#ifndef ASCIINEM_SERVER_NETWORK_FACTORY_HPP
#define ASCIINEM_SERVER_NETWORK_FACTORY_HPP

#include "server/network/asio_network.hpp"
#include "server/network/interfaces/connection_manager.hpp"
#include "server/network/interfaces/listener.hpp"
#include "server/network/interfaces/queue.hpp"
#include "server/network/interfaces/subject.hpp"
#include "server/network/server_config.hpp"
#include "server/network/types.hpp"

#include <utility>

namespace asciinem::server::network
{

// abstract factory
class network_factory
{
public:
    network_factory(const network_factory&) = delete;
    network_factory(network_factory&&) noexcept = delete;
    auto operator=(const network_factory&) -> network_factory& = delete;
    auto operator=(network_factory&&) noexcept -> network_factory& = delete;

    virtual ~network_factory() = default;

    [[nodiscard]] virtual auto make_queue() const -> queue::pointer = 0;
    [[nodiscard]] virtual auto make_listener(
        types::port,
        connection_manager::pointer
    ) const -> listener::pointer = 0;
    [[nodiscard]] virtual auto make_manager(
        queue::pointer dl,
        queue::pointer ul,
        subject::pointer clock
    ) const -> connection_manager::pointer = 0;

protected:
    network_factory() = default;
};

inline auto create_network(
    const server_config& config,
    const network_factory& factory,
    const subject::pointer& clock
)
{
    auto dl = factory.make_queue();
    auto ul = factory.make_queue();

    auto manager = factory.make_manager(dl, ul, clock);

    return std::make_unique<asio_network>(
        config.port,
        dl,
        ul,
        clock,
        manager,
        factory.make_listener(config.port, manager)
    );
}

} // namespace asciinem::server::network

#endif // ASCIINEM_SERVER_NETWORK_FACTORY_HPP
