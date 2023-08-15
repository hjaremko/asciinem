#ifndef ASCIINEM_SERVER_NETWORK_MODULE_HPP
#define ASCIINEM_SERVER_NETWORK_MODULE_HPP

#include "server/network/types.hpp"

#include <memory>

namespace asciinem::server::network
{

// facade
class network_module
{
public:
    using pointer = std::unique_ptr<network_module>;

    network_module() = default;
    network_module(const network_module&) = default;
    network_module(network_module&&) noexcept = default;
    auto operator=(const network_module&) -> network_module& = default;
    auto operator=(network_module&&) noexcept -> network_module& = default;

    virtual ~network_module() = default;

    virtual auto poll_message() -> types::msg = 0;
    virtual void queue_message(const types::msg&) = 0;
    [[nodiscard]] virtual auto has_message_available() const -> bool = 0;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_SERVER_NETWORK_MODULE_HPP
