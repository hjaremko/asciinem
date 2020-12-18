#include "client/network/asio_network_module.hpp"

#include <spdlog/spdlog.h>

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

auto asio_network_module::establish( const types::ip& ip, types::port port )
    -> bool
{
    spdlog::info( "Connecting to {}:{}...", ip, port );

    try
    {
        auto c = server::network::make_connection( io_context, ip, port, 0 );
        auto ack = c->receive_data();

        if ( ack != "confirm!" )
        {
            spdlog::error( "Invalid confirmation message: {}", ack );
            return false;
        }

        connection = c;
    }
    catch ( std::exception& )
    {
        spdlog::warn( "Failed connecting to server {}:{}", ip, port );
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
