#include "mocks/client_connection_mock.hpp"
#include "mocks/clock_mock.hpp"
#include "mocks/queue_mock.hpp"
#include "server/network/asio_connection.hpp"
#include "server/network/asio_listener.hpp"
#include "server/network/asio_manager.hpp"

#include <catch2/catch.hpp>

using namespace std::chrono_literals;
using namespace asciinem::server::network;

TEST_CASE( "Manager add/remove client test", "[network][manager]" )
{
    using asio::ip::tcp;
    using namespace ::testing;
    spdlog::default_logger_raw()->set_level( spdlog::level::trace );

    auto up = std::make_shared<queue_mock>();
    auto dl = std::make_shared<queue_mock>();
    auto clock = clock_mock {};

    constexpr auto port = 5555;
    const auto localhost = std::string { "127.0.0.1" };

    auto m = std::make_shared<asio_manager>( dl, up, clock );
    auto l = asio_listener { port, m };

    auto add_client = [ & ]( int i )
    {
        auto io_context = asio::io_context {};
        auto c =
            make_connection( io_context, localhost, port, std::to_string( i ) );
        c->receive_data();
        c->send_data( "login" );
        c->receive_data();
    };

    auto t1 = std::async( add_client, 0 );
    auto t2 = std::async( add_client, 1 );
    auto t3 = std::async( add_client, 2 );
    std::this_thread::sleep_for( 1s );
}

TEST_CASE( "Manager should broadcast to all connections", "[network][manager]" )
{
    using asio::ip::tcp;
    using namespace ::testing;
    spdlog::default_logger_raw()->set_level( spdlog::level::trace );

    auto up = std::make_shared<queue_mock>();
    auto dl = std::make_shared<queue_mock>();
    auto clock = clock_mock {};

    constexpr auto port = 5555;
    const auto localhost = std::string { "127.0.0.1" };

    auto m = std::make_shared<asio_manager>( dl, up, clock );
    auto l = asio_listener { port, m };

    auto add_client = [ & ]( int i )
    {
        auto io_context = asio::io_context {};
        auto c =
            make_connection( io_context, localhost, port, std::to_string( i ) );
        c->receive_data();
        c->send_data( "login" );
        c->receive_data();
        c->receive_data();
        spdlog::debug( "{} stopped receiving", c->id() );
    };

    auto t1 = std::async( add_client, 0 );
    auto t2 = std::async( add_client, 1 );
    auto t3 = std::async( add_client, 2 );

    std::this_thread::sleep_for( 1s );

    m->broadcast( "expected" );

    std::this_thread::sleep_for( 5s );
}
