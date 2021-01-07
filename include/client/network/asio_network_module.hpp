#ifndef ASCIINEM_CLIENT_ASIO_NETWORK_MODULE_HPP
#define ASCIINEM_CLIENT_ASIO_NETWORK_MODULE_HPP

#include "client/network/interfaces/network_module.hpp"
#include "server/network/asio_connection.hpp"
#include "server/network/message_queue.hpp"

#include <asio.hpp>
#include <optional>

namespace asciinem::client::network
{

class asio_network_module : public network_module
{
public:
    using connection_ptr = server::network::client_connection::pointer;

    asio_network_module() = default;
    asio_network_module( const asio_network_module& ) = delete;
    asio_network_module( asio_network_module&& ) noexcept = delete;
    auto operator=( const asio_network_module& )
        -> asio_network_module& = delete;
    auto operator=( asio_network_module&& ) noexcept
        -> asio_network_module& = delete;

    ~asio_network_module() override;

    auto poll_message() -> types::msg override;
    auto has_message_available() -> bool override;
    void queue_message( const types::msg& msg ) override;
    auto establish( const types::ip&, types::port, const std::string& ) -> bool;

private:
    void start_receiving();
    void start_sending();
    static auto get_most_recent_packet( const std::string& data )
        -> std::optional<std::string>;
    static auto split_merged_packets( const std::string& data )
        -> std::vector<std::string>;

    server::network::message_queue dl;
    server::network::message_queue ul;
    asio::io_context io_context;
    connection_ptr connection;
    std::atomic_bool running_ { true };
    std::optional<std::thread> sending_thread_;
    std::optional<std::thread> receiving_thread_;
};

} // namespace asciinem::client::network

#endif // ASCIINEM_CLIENT_ASIO_NETWORK_MODULE_HPP
