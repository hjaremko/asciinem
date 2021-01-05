#ifndef ASCIINEM_NETWORK_SERVICE_MEDIATOR_HPP
#define ASCIINEM_NETWORK_SERVICE_MEDIATOR_HPP

#include "serializer.hpp"
#include "server/service/request_serializer.hpp"

namespace asciinem::server
{

class network_service_mediator
{
public:
    explicit network_service_mediator( network::subject& clock,
                                       network::network_module& net,
                                       service::game_service& game )
        : net_( net ), game_( game )
    {
        clock.attach( observer_ );
    }

    void exchange_data()
    {
        if ( net_.has_message_available() )
        {
            spdlog::info( "New message available!" );
            auto request = serializer_.deserialize( net_.poll_message() );

            if ( request.has_value() )
            {
                ( *request )();
            }
            // request_handler_.add_request(request);
            // -> service.handle(req) -> req.execute();
        }

        net_.queue_message( serializer::serialize( game_.get_state() ) );
        game_.tick();
    }

private:
    network::clock_observer::pointer observer_ { network::make_clock_observer(
        "Network Service observer", [ this ] { exchange_data(); } ) };

    network::network_module& net_;
    service::game_service& game_;
    //    service::chat_service& chat_;
    service::request_serializer serializer_ { game_ };
};

} // namespace asciinem::server

#endif // ASCIINEM_NETWORK_SERVICE_MEDIATOR_HPP
