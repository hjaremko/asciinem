#include "client/network/asio_network_module.hpp"

#include "server/network/server_config.hpp"
#include "server/serializer.hpp"

#include <spdlog/spdlog.h>

namespace
{

auto send_login_request(
    const asciinem::server::network::client_connection::pointer& conn,
    const std::string& login
) -> std::string
{
    spdlog::info("Logging in with login {}...", login);

    conn->send_data(login);
    return conn->receive_data();
}

} // namespace

namespace asciinem::client::network
{

asio_network_module::~asio_network_module()
{
    auto join_thread = [](auto& t)
    {
        if (t.has_value())
        {
            spdlog::trace("Joining...");
            t->join();
        }
    };

    connection->disconnect();
    running_.store(false);
    join_thread(sending_thread_);
    join_thread(receiving_thread_);
}

auto asio_network_module::poll_message() -> types::msg
{
    auto data = dl.pop();
    data.pop_back();
    return data;
}

auto asio_network_module::has_message_available() -> bool
{
    return !dl.empty();
}

void asio_network_module::queue_message(const types::msg& msg)
{
    ul.push(msg);
}

auto asio_network_module::establish(
    const types::ip& ip,
    types::port port,
    const std::string& login
) -> bool
{
    spdlog::info("Connecting to {}:{}...", ip, port);

    try
    {
        auto c = server::network::make_connection(io_context, ip, port, login);

        spdlog::info("Waiting for confirmation message...");
        auto ack = c->receive_data();
        ack.pop_back();

        if (ack != "confirm!")
        {
            spdlog::error("Invalid confirmation message: {}", ack);
            return false;
        }

        auto response = send_login_request(c, login);
        response.pop_back();
        spdlog::info("Server response: {}", response);

        if (response != "OK")
        {
            spdlog::error("Login failed.");
            c->disconnect();
            return false;
        }

        connection = c;
    }
    //    catch ( login_failed_exception )
    //    {
    //    }
    catch (std::exception& e)
    {
        spdlog::error(
            "Failed connecting to server {}:{}. Reason: ",
            ip,
            port,
            e.what()
        );
        return false;
    }

    spdlog::info("Connected!");
    start_receiving();
    start_sending();
    return true;
}

auto asio_network_module::split_merged_packets(const std::string& data)
    -> std::vector<std::string>
{
    using server::network::server_config;

    auto buffer = std::stringstream{data};
    auto packets = std::vector<std::string>{};

    for (auto line = std::string{};
         std::getline(buffer, line, server_config::PACKET_DELIM);)
    {
        packets.push_back(line);
    }

    return packets;
}

auto asio_network_module::get_most_recent_packet(const std::string& data)
    -> std::optional<std::string>
{
    auto packets = split_merged_packets(data);

    if (auto p = std::find_if(
            std::rbegin(packets),
            std::rend(packets),
            server::serializer::is_complete
        );
        p != std::rend(packets))
    {
        return *p;
    }

    return std::nullopt;
}

void asio_network_module::start_receiving()
{
    auto poller = [this]()
    {
        spdlog::info("Waiting for server messages...");

        while (running_.load())
        {
            try
            {
                auto received = connection->receive_data();
                auto packet = get_most_recent_packet(received);

                if (packet.has_value())
                {
                    dl.push(*packet);
                }
            }
            catch (std::exception&)
            {
                break;
            }
        }

        spdlog::info("Disconnected from server");
    };

    receiving_thread_ = std::thread(poller);
}

void asio_network_module::start_sending()
{
    auto sender = [this]()
    {
        spdlog::info("Sending messages from the queue...");

        while (running_.load())
        {
            try
            {
                connection->send_data(ul.pop_wait());
            }
            catch (std::exception&)
            {
                break;
            }
        }

        spdlog::info("Stopped sending.");
    };

    sending_thread_ = std::thread(sender);
}

} // namespace asciinem::client::network
