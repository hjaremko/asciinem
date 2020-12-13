#ifndef ASCIINEM_ASIO_LISTENER_HPP
#define ASCIINEM_ASIO_LISTENER_HPP

#include "asio_tcp_server.hpp"
#include "interfaces/client_connection.hpp"
#include "interfaces/connection_manager.hpp"
#include "interfaces/listener.hpp"

#include <asio.hpp>
#include <optional>
#include <spdlog/spdlog.h>
#include <string>

namespace asciinem::server::network
{

class asio_listener : public listener
{
public:
    asio_listener( types::port port, connection_manager& manager );

    asio_listener( const asio_listener& ) = delete;
    asio_listener( asio_listener&& ) noexcept = delete;
    auto operator=( const asio_listener& ) -> asio_listener& = delete;
    auto operator=( asio_listener&& ) noexcept -> asio_listener& = delete;
    ~asio_listener() override;

    void start_listening() override;
    void stop_listening() override;

private:
    void start_listening_();
    void stop_listening_();

    types::port port_;
    asio::io_context io_context_;
    asio_server tcp_server_;
    std::optional<std::thread> thread_;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_ASIO_LISTENER_HPP
