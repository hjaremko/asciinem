#ifndef ASCIINEM_CONNECTION_MANAGER_MOCK_HPP
#define ASCIINEM_CONNECTION_MANAGER_MOCK_HPP

#include "network/interfaces/client_connection.hpp"
#include "network/interfaces/connection_manager.hpp"
#include "network/types.hpp"

#include "gmock/gmock.h"
#include <deque>

class connection_manager_mock
    : public asciinem::server::network::connection_manager
{
public:
    MOCK_METHOD( void,
                 add_client,
                 ( asciinem::server::network::client_connection::pointer ),
                 () );
    MOCK_METHOD( void,
                 remove_client,
                 ( asciinem::server::network::types::id ),
                 () );
    MOCK_METHOD( void, broadcast, (), () );
    MOCK_METHOD( std::deque<asciinem::server::network::types::msg>,
                 poll_clients,
                 (),
                 () );
};

#endif // ASCIINEM_CONNECTION_MANAGER_MOCK_HPP
