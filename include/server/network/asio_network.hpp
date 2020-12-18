#ifndef ASCIINEM_SERVER_ASIO_NETWORK_HPP
#define ASCIINEM_SERVER_ASIO_NETWORK_HPP

#include "network/interfaces/connection_manager.hpp"
#include "network/interfaces/listener.hpp"
#include "network/interfaces/network_module.hpp"
#include "network/interfaces/queue.hpp"
#include "network/interfaces/subject.hpp"
#include "network/types.hpp"

namespace asciinem::server::network
{

class asio_network : public network_module
{
public:
    asio_network( types::ip ip,
                  types::port port,
                  queue::pointer dl,
                  queue::pointer ul,
                  subject::pointer clock,
                  connection_manager::pointer manager,
                  listener::pointer listener )
        : ip_( std::move( ip ) ), port_( port ), dl_( std::move( dl ) ),
          ul_( std::move( ul ) ), clock_( std::move( clock ) ),
          manager_( std::move( manager ) ), listener_( std::move( listener ) )
    {
    }

    auto poll_message() -> types::msg override
    {
        return dl_->pop_wait();
    }

    void queue_message( const types::msg& msg ) override
    {
        ul_->push( msg );
    }

private:
    types::ip ip_;
    types::port port_;
    queue::pointer dl_;
    queue::pointer ul_;
    subject::pointer clock_;
    connection_manager::pointer manager_;
    listener::pointer listener_;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_SERVER_ASIO_NETWORK_HPP
