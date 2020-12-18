#ifndef ASCIINEM_CLIENT_CONNECTION_HPP
#define ASCIINEM_CLIENT_CONNECTION_HPP

#include "server/network/types.hpp"
#include "queue.hpp"

#include <memory>

namespace asciinem::server::network
{

class client_connection
{
public:
    using pointer = std::shared_ptr<client_connection>;

    client_connection() = default;
    client_connection( const client_connection& ) = default;
    client_connection( client_connection&& ) noexcept = default;
    auto operator=( const client_connection& ) -> client_connection& = default;
    auto operator=( client_connection&& ) noexcept
        -> client_connection& = default;

    virtual ~client_connection() = default;

    virtual auto id() -> types::id = 0;
    virtual auto ip() -> types::ip = 0;
    virtual auto receive_data() -> types::msg = 0;
    virtual void send_data( const types::msg& msg ) = 0;
    virtual void disconnect() = 0;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_CLIENT_CONNECTION_HPP
