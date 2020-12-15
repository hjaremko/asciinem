#ifndef ASCIINEM_ASIO_MANAGER_HPP
#define ASCIINEM_ASIO_MANAGER_HPP

#include "interfaces/connection_manager.hpp"
#include "interfaces/queue.hpp"

#include <future>
#include <list>
#include <thread>

namespace asciinem::server::network
{

class asio_manager : public connection_manager
{
private:
    using connection_poller_pair =
        std::pair<client_connection::pointer, std::thread>;

public:
    explicit asio_manager( queue::pointer dl, queue::pointer up );

    asio_manager( const asio_manager& ) = delete;
    asio_manager( asio_manager&& ) noexcept = delete;
    auto operator=( const asio_manager& ) -> asio_manager& = delete;
    auto operator=( asio_manager&& ) noexcept -> asio_manager& = delete;

    ~asio_manager() override;

    void add_client( client_connection::pointer client ) override;
    void remove_client( types::id client_id ) override;
    auto poll_client( const client_connection::pointer& c ) -> std::thread;
    [[nodiscard]] auto connected_players() const -> int override;

private:
    std::mutex mutex_;
    std::list<connection_poller_pair> clients_;
    queue::pointer downlink_;
    queue::pointer uplink_;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_ASIO_MANAGER_HPP
