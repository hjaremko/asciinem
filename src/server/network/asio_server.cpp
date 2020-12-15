#include "network/asio_server.hpp"

#include <spdlog/spdlog.h>

namespace asciinem::server::network
{

asio_server::asio_server( types::port port,
                          asio::io_context& io_context,
                          connection_manager& manager )
    : port_( port ), io_context_( io_context ), manager_( manager )
{
    start_accept();
}

void asio_server::start_accept()
{
    auto new_connection = make_connection( io_context_, id_pool_.next_id() );

    acceptor_.async_accept( new_connection->socket(),
                            [ this, new_connection ]( auto error_code ) {
                                handle_accept( new_connection, error_code );
                            } );
}

void asio_server::handle_accept( const asio_connection::pointer& new_connection,
                                 const asio::error_code& error )
{
    if ( !error )
    {
        spdlog::info( "Accepted connection from {}.", new_connection->ip() );

        new_connection->send_confirmation();
        manager_.add_client( new_connection );
    }

    start_accept();
}

} // namespace asciinem::server::network
