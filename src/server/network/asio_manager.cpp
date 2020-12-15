#include "network/asio_manager.hpp"

#include <spdlog/spdlog.h>

namespace asciinem::server::network
{

asio_manager::asio_manager( queue::pointer dl, queue::pointer up )
    : downlink_( std::move( dl ) ), uplink_( std::move( up ) )
{
}

asio_manager::~asio_manager()
{
    for ( auto& [ c, poller ] : clients_ )
    {
        c->disconnect();
        poller.join();
    }
}

void asio_manager::add_client( client_connection::pointer client )
{
    auto l = std::unique_lock<std::mutex> { mutex_ };

    auto poller = poll_client( client );

    spdlog::debug(
        "Adding new client: id: {}, ip: {}", client->id(), client->ip() );

    clients_.emplace_back(
        std::make_pair( std::move( client ), std::move( poller ) ) );

    spdlog::debug( "Connected clients: {}", connected_players() );
}

void asio_manager::remove_client( types::id client_id )
{
    auto l = std::unique_lock<std::mutex> { mutex_ };

    spdlog::debug( "Removing client: {}", client_id );

    auto to_remove = std::find_if(
        std::begin( clients_ ),
        std::end( clients_ ),
        [ client_id ]( const auto& c ) { return c.first->id() == client_id; } );

    to_remove->second.detach(); // todo: ugly
    clients_.erase( to_remove );

    spdlog::debug( "Connected clients: {}", connected_players() );
}

auto asio_manager::poll_client( const client_connection::pointer& c )
    -> std::thread
{
    auto poller = [ this, dl = downlink_->shared_from_this() ](
                      const client_connection::pointer& client ) {
        spdlog::debug( "Polling client id {}", client->id() );

        while ( true )
        {
            try
            {
                auto received = client->receive_data();
                dl->push( received );
            }
            catch ( std::exception& e )
            {
                break;
            }
        }

        spdlog::debug( "Stopped polling client id {}", client->id() );
        remove_client( client->id() );
    };

    return std::thread( poller, ( c ) );
}

auto asio_manager::connected_players() const -> int
{
    return static_cast<int>( clients_.size() );
}

} // namespace asciinem::server::network
