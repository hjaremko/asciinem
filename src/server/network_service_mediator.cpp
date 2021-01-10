#include "server/network_service_mediator.hpp"

#include "server/serializer.hpp"

namespace asciinem::server
{

network_service_mediator::network_service_mediator(
    network::subject& clock,
    network::network_module& net,
    service::game_service& game )
    : net_( net ), game_( game )
{
    clock.attach( observer_ );
}

void network_service_mediator::exchange_data()
{
    if ( net_.has_message_available() )
    {
        spdlog::info( "New message available!" );
        auto request = serializer_.deserialize( net_.poll_message() );

        if ( request.has_value() )
        {
            ( *request )();
        }
    }

    net_.queue_message( serializer::serialize( game_.get_state() ) );
    game_.tick();
}

} // namespace asciinem::server
