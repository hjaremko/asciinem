#include "server/network/asio_server.hpp"

#include <spdlog/spdlog.h>

namespace asciinem::server::network
{

asio_server::asio_server( types::port port,
                          asio::io_context& io_context,
                          connection_manager::pointer manager )
    : port_( port ), io_context_( io_context ), manager_( std::move( manager ) )
{
    start_accept();
}

void asio_server::start_accept()
{
    auto new_connection = make_connection( io_context_, "" );

    acceptor_.async_accept( new_connection->socket(),
                            [ this, new_connection ]( auto error_code )
                            { handle_accept( new_connection, error_code ); } );
}

void asio_server::handle_accept( const asio_connection::pointer& new_connection,
                                 const asio::error_code& error )
{
    if ( !error )
    {
        spdlog::info( "Accepted connection from {}.", new_connection->ip() );

        new_connection->send_confirmation();
        auto login = new_connection->receive_data();
        login.pop_back();

        if ( manager_->is_logged( login ) )
        {
            auto already_logged_msg = fmt::format(
                "{} is already logged in! Refusing connection.", login );

            spdlog::info( already_logged_msg );
            new_connection->send_data( already_logged_msg );
        }
        else
        {
            new_connection->id() = login;
            new_connection->send_data( "OK" );
            manager_->add_client( new_connection );
        }
    }

    start_accept();
}

} // namespace asciinem::server::network
