#ifndef ASCIINEM_CONNECTION_MANAGER_HPP
#define ASCIINEM_CONNECTION_MANAGER_HPP

#include "client_connection.hpp"
#include "server/network/types.hpp"

#include <deque>

namespace asciinem::server::network
{

class connection_manager
{
public:
    using pointer = std::shared_ptr<connection_manager>;

    connection_manager() = default;
    connection_manager( const connection_manager& ) = default;
    connection_manager( connection_manager&& ) noexcept = default;
    auto operator=( const connection_manager& )
        -> connection_manager& = default;
    auto operator=( connection_manager&& ) noexcept
        -> connection_manager& = default;

    virtual ~connection_manager() = default;

    virtual void add_client( client_connection::pointer ) = 0;
    virtual void remove_client( types::id client_id ) = 0;
    [[nodiscard]] virtual auto connected_players() const -> int = 0;
    virtual void broadcast( const types::msg& msg ) const = 0;
    virtual auto is_logged( const std::string& ) const -> bool = 0;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_CONNECTION_MANAGER_HPP
