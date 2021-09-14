#ifndef ASCIINEM_ASIO_CONNECTION_HPP
#define ASCIINEM_ASIO_CONNECTION_HPP

#include "interfaces/client_connection.hpp"
#include "interfaces/queue.hpp"

#include <asio.hpp>

namespace asciinem::server::network
{

class asio_connection : public std::enable_shared_from_this<asio_connection>,
                        public client_connection
{
public:
    using pointer = std::shared_ptr<asio_connection>;

    explicit asio_connection( asio::io_context&, types::id );
    asio_connection( asio::io_context&,
                     const types::ip&,
                     types::port,
                     types::id );

    asio_connection( const asio_connection& ) = delete;
    asio_connection( asio_connection&& ) noexcept = default;
    auto operator=( const asio_connection& ) -> asio_connection& = delete;
    auto operator=( asio_connection&& ) noexcept -> asio_connection& = delete;
    ~asio_connection() override;

    auto id() -> types::id& override;
    auto ip() -> types::ip override;
    auto receive_data() -> types::msg override;
    void send_data( const types::msg& ) override;
    auto socket() -> asio::ip::tcp::socket&;
    void send_confirmation();
    void disconnect() override;

private:
    void disconnect_();

    asio::ip::tcp::socket socket_;
    types::id id_ { 0 };
};

auto make_connection( asio::io_context&, const types::id& )
    -> asio_connection::pointer;

auto make_connection( asio::io_context&,
                      const types::ip&,
                      types::port,
                      const types::id& ) -> asio_connection::pointer;

} // namespace asciinem::server::network

#endif // ASCIINEM_ASIO_CONNECTION_HPP
