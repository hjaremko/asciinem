#ifndef ASCIINEM_CLIENT_NETWORK_MODULE_HPP
#define ASCIINEM_CLIENT_NETWORK_MODULE_HPP

#include "client/network/types.hpp"

namespace asciinem::client::network
{

class network_module
{
public:
    network_module() = default;
    network_module( const network_module& ) = default;
    network_module( network_module&& ) noexcept = default;
    auto operator=( const network_module& ) -> network_module& = default;
    auto operator=( network_module&& ) noexcept -> network_module& = default;

    virtual ~network_module() = default;

    virtual auto poll_message() -> types::msg = 0;
    virtual void queue_message( const types::msg& ) = 0;
};

} // namespace asciinem::client::network

#endif // ASCIINEM_CLIENT_NETWORK_MODULE_HPP
