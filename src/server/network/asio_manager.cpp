#include "server/network/asio_manager.hpp"

#include "server/network/interfaces/subject.hpp"
#include "server/service/request.hpp"

namespace asciinem::server::network
{

asio_manager::asio_manager(queue::pointer dl, queue::pointer up, subject& c)
    : downlink_(std::move(dl))
    , uplink_(std::move(up))
    , observer_(make_clock_observer())
{
    c.attach(observer_);
}

asio_manager::~asio_manager()
{
    for (auto& [c, poller] : clients_)
    {
        c->disconnect();
        poller.join();
    }

    spdlog::info("Connection Manager shut down");
}

void asio_manager::add_client(client_connection::pointer client)
{
    spdlog::trace("Waiting on a connection manager mutex...");
    auto l = std::lock_guard<std::recursive_mutex>{mutex_};

    auto login = client->id();
    auto poller = poll_client(client);

    spdlog::debug(
        "Adding new client: id: {}, ip: {}",
        client->id(),
        client->ip()
    );

    clients_.emplace_back(std::make_pair(std::move(client), std::move(poller)));

    spdlog::debug("Connected clients: {}", connected_players());

    this->downlink_->push(service::request::make_login_request(login));
}

void asio_manager::remove_client(types::id client_id)
{
    spdlog::trace("Remove client waiting on a connection manager mutex...");
    auto l = std::lock_guard<std::recursive_mutex>{mutex_};

    spdlog::debug("Removing client: {}", client_id);

    auto to_remove = std::find_if(
        std::begin(clients_),
        std::end(clients_),
        [client_id](const auto& c)
        {
            return c.first->id() == client_id;
        }
    );

    auto login = to_remove->first->id();
    to_remove->second.detach();
    clients_.erase(to_remove);

    spdlog::debug("Connected clients: {}", connected_players());

    this->downlink_->push(service::request::make_logout_request(login));
}

auto asio_manager::poll_client(const client_connection::pointer& c)
    -> std::thread
{
    auto poller = [this, dl = downlink_->shared_from_this()](
                      const client_connection::pointer& client
                  )
    {
        spdlog::info("Polling client id {}", client->id());

        while (true)
        {
            try
            {
                auto received = client->receive_data();
                dl->push(received);
            }
            catch (std::exception&)
            {
                break;
            }
        }

        spdlog::info("Stopped polling client id {}", client->id());
        remove_client(client->id());
        spdlog::info("Poller id {} thread ended", client->id());
    };

    return std::thread(poller, (c));
}

auto asio_manager::connected_players() const -> int
{
    return static_cast<int>(clients_.size());
}

auto asio_manager::make_clock_observer() const -> clock_observer::pointer
{
    return std::make_shared<clock_observer>(
        "Manager Clock Observer",
        [this]()
        {
            broadcast_next();
        }
    );
}

void asio_manager::broadcast(const types::msg& msg) const
{
    spdlog::trace("Waiting on a connection manager mutex...");
    auto l = std::lock_guard<std::recursive_mutex>{mutex_};

    spdlog::trace("Broadcasting message '{}'", msg);

    for (const auto& client : clients_)
    {
        client.first->send_data(msg);
    }
}

void asio_manager::broadcast_next() const
{
    if (uplink_->empty())
    {
        spdlog::warn("Nothing to broadcast.");
        return;
    }

    auto msg = uplink_->pop();
    broadcast(msg);
}

auto asio_manager::is_logged(const std::string& login) const -> bool
{
    return std::find_if(
               std::begin(clients_),
               std::end(clients_),
               [&](const auto& c)
               {
                   return c.first->id() == login;
               }
           )
        != std::end(clients_);
}

} // namespace asciinem::server::network
