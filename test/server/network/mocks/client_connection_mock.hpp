#ifndef ASCIINEM_CLIENT_CONNECTION_MOCK_HPP
#define ASCIINEM_CLIENT_CONNECTION_MOCK_HPP

#include "server/network/interfaces/client_connection.hpp"
#include "server/network/interfaces/queue.hpp"
#include "server/network/types.hpp"

#include "gmock/gmock.h"

class client_connection_mock
    : public asciinem::server::network::client_connection
{
public:
    MOCK_METHOD( asciinem::server::network::types::id&, id, (), () );
    MOCK_METHOD( asciinem::server::network::types::ip, ip, (), () );
    MOCK_METHOD( asciinem::server::network::types::msg, receive_data, (), () );
    MOCK_METHOD( void,
                 send_data,
                 ( const asciinem::server::network::types::msg& ),
                 () );
    MOCK_METHOD( void, disconnect, (), ( override ) );
};

#endif // ASCIINEM_CLIENT_CONNECTION_MOCK_HPP
