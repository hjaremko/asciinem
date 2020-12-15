#include "mocks/client_connection_mock.hpp"
#include "mocks/queue_mock.hpp"
#include "network/asio_connection.hpp"
#include "network/asio_listener.hpp"
#include "network/asio_manager.hpp"

#include <catch2/catch.hpp>

using namespace std::chrono_literals;
using namespace asciinem::server::network;

TEST_CASE( "Manager add/remove client test", "[network], [manager]" )
{
    using asio::ip::tcp;
    using namespace ::testing;
    spdlog::default_logger_raw()->set_level( spdlog::level::trace );

    auto up = std::make_shared<queue_mock>();
    auto dl = std::make_shared<queue_mock>();

    constexpr auto port = 5555;
    const auto localhost = std::string { "127.0.0.1" };

    auto m = asio_manager { dl, up };
    auto l = asio_listener { port, m };

    auto io_context0 = asio::io_context {};

    auto add_client = [ & ]( int i ) {
        auto c0 = make_connection( io_context0, localhost, port, i );
        c0->receive_data();
    };

    auto t1 = std::async( add_client, 0 );
    auto t2 = std::async( add_client, 1 );
    auto t3 = std::async( add_client, 2 );
    std::this_thread::sleep_for( 1s );
}
