#include "network/asio_connection.hpp"

#include <asio.hpp>
#include <spdlog/spdlog.h>

namespace asciinem::server::network
{

asio_connection::asio_connection( asio::io_context& io_context )
    : socket_( io_context )
{
}

asio_connection::asio_connection( asio::io_context& io_context,
                                  const types::ip& ip,
                                  types::port port )
    : socket_( io_context )
{
    auto resolver = asio::ip::tcp::resolver { io_context };
    auto endpoints = resolver.resolve( ip, std::to_string( port ) );
    asio::connect( socket_, endpoints );
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
    auto array_to_str = []( const auto& buffer, auto size ) {
        auto ss = std::stringstream {};
        ss.write( buffer.data(), static_cast<long>( size ) );
        return ss.str();
    };

    constexpr const auto buffer_size = 128;
    using buffer_type = std::array<char, buffer_size>;

    auto receive_from_socket =
        [ this ]() -> std::pair<buffer_type, std::size_t> {
        auto buffer = buffer_type { {} };
        auto error = asio::error_code {};

        auto len = static_cast<long long int>(
            socket_.read_some( asio::buffer( buffer ), error ) );

        return { buffer, len };
    };

    auto [ buffer, bytes ] = receive_from_socket();
    auto received_message = array_to_str( buffer, bytes );

    spdlog::debug(
        "Connection {} received {} bytes from {}", id(), bytes, ip() );
    spdlog::debug(
        "Connection {} received message: '{}'", id(), received_message );

    return received_message;
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
    spdlog::debug( "Sent data to connection id: {}, ip: {}", id(), ip() );
}

auto make_connection( asio::io_context& io_context ) -> asio_connection::pointer
{
    return std::make_shared<asio_connection>( io_context );
}

auto make_connection( asio::io_context& io_context,
                      const types::ip& ip,
                      types::port port ) -> asio_connection::pointer
{
    return std::make_shared<asio_connection>( io_context, ip, port );
}

} // namespace asciinem::server::network
