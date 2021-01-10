#ifndef ASCIINEM_SERVER_REQUEST_SERIALIZER_HPP
#define ASCIINEM_SERVER_REQUEST_SERIALIZER_HPP

#include "server/network/types.hpp"
#include "server/service/game_service.hpp"
#include "server/service/request.hpp"

namespace asciinem::server::service
{

// command
class request_serializer
{
public:
    explicit request_serializer( game_service& game );

    auto deserialize( const network::types::msg& msg )
        -> std::optional<request>;

private:
    game_service& game_;
    //    service::chat_service& chat_;
};

} // namespace asciinem::server::service

#endif // ASCIINEM_SERVER_REQUEST_SERIALIZER_HPP
