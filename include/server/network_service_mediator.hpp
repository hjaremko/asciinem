#ifndef ASCIINEM_NETWORK_SERVICE_MEDIATOR_HPP
#define ASCIINEM_NETWORK_SERVICE_MEDIATOR_HPP

#include "server/network/clock_observer.hpp"
#include "server/network/interfaces/network_module.hpp"
#include "server/network/interfaces/subject.hpp"
#include "server/service/game_service.hpp"
#include "server/service/request_serializer.hpp"

namespace asciinem::server
{

// mediator
class network_service_mediator
{
public:
    explicit network_service_mediator( network::subject& clock,
                                       network::network_module& net,
                                       service::game_service& game );

    void exchange_data();

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
