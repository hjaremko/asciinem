#ifndef ASCIINEM_ASIO_SERVER_HPP
#define ASCIINEM_ASIO_SERVER_HPP

#include "asio_connection.hpp"
#include "id_pool.hpp"
#include "interfaces/connection_manager.hpp"
#include "types.hpp"

#include <asio.hpp>

namespace asciinem::server::network
{

class asio_server
{
public:
    [[maybe_unused]] explicit asio_server(
        types::port port,
        asio::io_context& io_context,
        connection_manager::pointer manager );

private:
    void start_accept();
    void handle_accept( const asio_connection::pointer& new_connection,
                        const asio::error_code& error );

    types::port port_;
    asio::io_context& io_context_;
    asio::ip::tcp::acceptor acceptor_ {
        io_context_, asio::ip::tcp::endpoint( asio::ip::tcp::v4(), port_ )
    };
    connection_manager::pointer manager_;
    id_pool id_pool_;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_ASIO_SERVER_HPP
