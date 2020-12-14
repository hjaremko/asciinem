#ifndef ASCIINEM_ASIO_CONNECTION_HPP
#define ASCIINEM_ASIO_CONNECTION_HPP

#include "interfaces/client_connection.hpp"

#include <asio.hpp>

namespace asciinem::server::network
{

class client_connection;

class asio_connection : public std::enable_shared_from_this<asio_connection>,
                        public client_connection
{
public:
    using pointer = std::shared_ptr<asio_connection>;

    explicit asio_connection( asio::io_context& io_context );
    asio_connection( asio::io_context& io_context,
                     const types::ip& ip,
                     types::port port );

    auto id() -> types::id override;
    auto ip() -> types::ip override;
    auto receive_data() -> types::msg override;
    void send_data( const types::msg& msg ) override;
    auto socket() -> asio::ip::tcp::socket&;
    void send_confirmation();

private:
    void handle_write();

    asio::ip::tcp::socket socket_;
};

auto make_connection( asio::io_context& io_context )
    -> asio_connection::pointer;

auto make_connection( asio::io_context& io_context,
                      const types::ip& ip,
                      types::port port ) -> asio_connection::pointer;

} // namespace asciinem::server::network

#endif // ASCIINEM_ASIO_CONNECTION_HPP
