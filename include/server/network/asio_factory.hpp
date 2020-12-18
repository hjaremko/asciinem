#ifndef ASCIINEM_SERVER_ASIO_FACTORY_HPP
#define ASCIINEM_SERVER_ASIO_FACTORY_HPP

#include "network/asio_listener.hpp"
#include "network/asio_manager.hpp"
#include "network/interfaces/network_factory.hpp"
#include "network/message_queue.hpp"

#include <memory>

namespace asciinem::server::network
{

class asio_factory : public network_factory
{
public:
    static auto instance() -> asio_factory&
    {
        static auto instance = asio_factory();
        return instance;
    }

    [[nodiscard]] auto make_queue() const -> queue::pointer override
    {
        return std::make_shared<network::message_queue>();
    }

    [[nodiscard]] auto
    make_listener( types::port port, connection_manager::pointer manager ) const
        -> listener::pointer override
    {
        return std::make_unique<network::asio_listener>( port, manager );
    }

    [[nodiscard]] auto make_manager( queue::pointer dl,
                                     queue::pointer ul,
                                     subject::pointer clock ) const
        -> connection_manager::pointer override
    {
        return std::make_shared<asio_manager>( dl, ul, *clock );
    }

private:
    asio_factory() = default;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_SERVER_ASIO_FACTORY_HPP
