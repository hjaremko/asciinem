#include "network/asio_connection.hpp"

#include <asio.hpp>
#include <spdlog/spdlog.h>

namespace asciinem::server::network
{

asio_connection::asio_connection( asio::io_context& io_context )
    : socket_( io_context )
{
}

auto asio_connection::id() -> types::id
{
    return 0; // todo
}

auto asio_connection::ip() -> types::ip
{
    return socket_.remote_endpoint().address().to_string();
}

auto asio_connection::receive_data() -> types::msg
{
    return "none"; // todo
}

void asio_connection::send_data( const types::msg& msg )
{
    spdlog::debug( "Sending '{}' to {}", msg, ip() );

    asio::async_write(
        socket_,
        asio::buffer( msg ),
        [ this_ptr = shared_from_this() ]( auto /*unused*/, auto /*unused*/ ) {
            this_ptr->handle_write();
        } );
}

auto asio_connection::socket() -> asio::ip::tcp::socket&
{
    return socket_;
}

void asio_connection::send_confirmation()
{
    spdlog::info( "Sending confirmation message to {}", ip() );

    auto message_ = std::string { "confirm!" };
    send_data( message_ );
}

void asio_connection::handle_write()
{
    spdlog::debug( "Sent data to connection id: {} , ip: {}", id(), ip() );
}

auto make_connection( asio::io_context& io_context ) -> asio_connection::pointer
{
    return std::make_shared<asio_connection>( io_context );
}

} // namespace asciinem::server::network
