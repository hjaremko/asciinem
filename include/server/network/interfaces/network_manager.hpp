#ifndef ASCIINEM_NETWORK_MANAGER_HPP
#define ASCIINEM_NETWORK_MANAGER_HPP

#include "server/network/types.hpp"

namespace asciinem::server::network
{

class network_manager
{
public:
    network_manager() = default;
    network_manager(const network_manager&) = default;
    network_manager(network_manager&&) noexcept = default;
    auto operator=(const network_manager&) -> network_manager& = default;
    auto operator=(network_manager&&) noexcept -> network_manager& = default;

    virtual ~network_manager() = default;

    virtual void queue_data(const types::msg& data) = 0;
    virtual auto poll_data() -> types::msg = 0;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_CLIENT_CONNECTION_HPP

#endif // ASCIINEM_NETWORK_MANAGER_HPP
