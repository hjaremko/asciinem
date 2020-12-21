#include "client/network/asio_network_module.hpp"

#include <spdlog/spdlog.h>

namespace
{

auto send_login_request(
    const asciinem::server::network::client_connection::pointer& conn,
    const std::string& login ) -> std::string
{
    spdlog::info( "Logging in with login {}...", login );

    conn->send_data( login );
    return conn->receive_data();
}

} // namespace

namespace asciinem::client::network
{

asio_network_module::~asio_network_module()
{
    auto join_thread = []( auto& t ) {
        if ( t.has_value() )
        {
            spdlog::trace( "Joining..." );
            t->join();
        }
    };

    connection->disconnect();
    running_.store( false );
    join_thread( sending_thread_ );
    join_thread( receiving_thread_ );
}

auto asio_network_module::poll_message() -> types::msg
{
    return dl.pop_wait();
}

void asio_network_module::queue_message( const types::msg& msg )
{
    ul.push( msg );
}

auto asio_network_module::establish( const types::ip& ip,
                                     types::port port,
                                     const std::string& login ) -> bool
{
    spdlog::info( "Connecting to {}:{}...", ip, port );

    try
    {
        auto c =
            server::network::make_connection( io_context, ip, port, login );

        spdlog::info( "Waiting for confirmation message..." );
        auto ack = c->receive_data();

        if ( ack != "confirm!" )
        {
            spdlog::error( "Invalid confirmation message: {}", ack );
            return false;
        }

        auto response = send_login_request( c, login );
        spdlog::info( "Server response: {}", response );

        if ( response != "OK" )
        {
            spdlog::error( "Login failed." );
            c->disconnect();
            return false;
        }

        connection = c;
    }
    //    catch ( login_failed_exception )
    //    {
    //    }
    catch ( std::exception& )
    {
        spdlog::error( "Failed connecting to server {}:{}", ip, port );
        return false;
    }

    spdlog::info( "Connected!" );
    start_receiving();
    start_sending();
    return true;
}

void asio_network_module::start_receiving()
{
    auto poller = [ this ]() {
        spdlog::info( "Waiting for server messages..." );

        while ( running_.load() )
        {
            try
            {
                auto received = connection->receive_data();
                dl.push( received );
            }
            catch ( std::exception& e )
            {
                break;
            }
        }

        spdlog::info( "Server disconnected." );
        // todo: notify observer
    };

    receiving_thread_ = std::thread( poller );
}

void asio_network_module::start_sending()
{
    auto sender = [ this ]() {
        spdlog::info( "Sending messages from the queue..." );

        while ( running_.load() )
        {
            try
            {
                connection->send_data( ul.pop_wait() );
            }
            catch ( std::exception& e )
            {
                break;
            }
        }

        spdlog::info( "Stopped sending." );
        // todo: notify observer
    };

    sending_thread_ = std::thread( sender );
}

} // namespace asciinem::client::network
