#ifndef ASCIINEM_CONNECTION_MANAGER_MOCK_HPP
#define ASCIINEM_CONNECTION_MANAGER_MOCK_HPP

#include "server/network/interfaces/client_connection.hpp"
#include "server/network/interfaces/connection_manager.hpp"
#include "server/network/types.hpp"

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
    MOCK_METHOD( std::deque<asciinem::server::network::types::msg>,
                 poll_clients,
                 (),
                 () );
    MOCK_METHOD( int, connected_players, (), ( const, override ) );
    MOCK_METHOD( void,
                 broadcast,
                 ( const asciinem::server::network::types::msg& ),
                 ( const, override ) );
    MOCK_METHOD( bool, is_logged, ( const std::string& ), ( const, override ) );
};

#endif // ASCIINEM_CONNECTION_MANAGER_MOCK_HPP
