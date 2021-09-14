#include "server/network/asio_connection.hpp"

#include <asio.hpp>
#include <server/network/server_config.hpp>
#include <spdlog/spdlog.h>
#include <utility>

namespace asciinem::server::network
{

asio_connection::asio_connection( asio::io_context& io_context, types::id id )
    : socket_( io_context ), id_( std::move( id ) )
{
    spdlog::trace( "New connection created {}", id_ );
}

asio_connection::asio_connection( asio::io_context& io_context,
                                  const types::ip& ip,
                                  types::port port,
                                  types::id id )
    : socket_( io_context ), id_( std::move( id ) )
{
    auto resolver = asio::ip::tcp::resolver { io_context };
    auto endpoints = resolver.resolve( ip, std::to_string( port ) );
    asio::connect( socket_, endpoints );
}

asio_connection::~asio_connection()
{
    disconnect_();
}

auto asio_connection::id() -> types::id&
{
    return id_;
}

auto asio_connection::ip() -> types::ip
{
    return socket_.remote_endpoint().address().to_string();
}

auto asio_connection::receive_data() -> types::msg
{
    auto array_to_str = []( const auto& buffer, auto size )
    {
        auto ss = std::stringstream {};
        ss.write( buffer.data(), static_cast<long>( size ) );
        return ss.str();
    };

    constexpr const auto buffer_size = 2048 * 8;
    using buffer_type = std::array<char, buffer_size>;

    auto receive_from_socket = [ this ]() -> std::pair<buffer_type, std::size_t>
    {
        auto buffer = buffer_type { {} };
        auto error = asio::error_code {};

        auto len = static_cast<long long int>(
            socket_.read_some( asio::buffer( buffer ), error ) );

        if ( error )
        {
            spdlog::warn( "Connection {} error: {}", id(), error.message() );
            throw std::runtime_error { error.message() };
        }

        return { buffer, len };
    };

    auto [ buffer, bytes ] = receive_from_socket();
    auto received_message = array_to_str( buffer, bytes );

    spdlog::trace(
        "Connection {} received {} bytes from {}", id(), bytes, ip() );
    spdlog::debug(
        "Connection {} received message: '{}'", id(), received_message );

    return received_message;
}

void asio_connection::send_data( const types::msg& msg )
{
    using server::network::server_config;

    spdlog::trace( "Sending '{}' to {} at {}", msg, id(), ip() );

    asio::write( socket_, asio::buffer( msg + server_config::PACKET_DELIM ) );
}

auto asio_connection::socket() -> asio::ip::tcp::socket&
{
    return socket_;
}

void asio_connection::send_confirmation()
{
    spdlog::debug( "Sending confirmation message to {}", ip() );

    auto message_ = std::string { "confirm!" };
    send_data( message_ );
}

void asio_connection::disconnect()
{
    disconnect_();
}

void asio_connection::disconnect_()
{
    spdlog::info( "Shutting down client {}", id_ );

    auto ec = asio::error_code {};
    socket_.shutdown( asio::ip::tcp::socket::shutdown_both, ec );
}

auto make_connection( asio::io_context& io_context, const types::id& id )
    -> asio_connection::pointer
{
    return std::make_shared<asio_connection>( io_context, id );
}

auto make_connection( asio::io_context& io_context,
                      const types::ip& ip,
                      types::port port,
                      const types::id& id ) -> asio_connection::pointer
{
    return std::make_shared<asio_connection>( io_context, ip, port, id );
}

} // namespace asciinem::server::network
