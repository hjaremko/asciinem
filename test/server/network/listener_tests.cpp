#include "mocks/connection_manager_mock.hpp"
#include "network/asio_listener.hpp"

#include <catch2/catch.hpp>

using namespace std::chrono_literals;
using namespace asciinem::server::network;

TEST_CASE( "Listener start/stop test", "[network], [listener]" )
{
    auto manager_mock = connection_manager_mock {};

    constexpr auto port = 5556;

    auto l = asio_listener { port, manager_mock };

    l.stop_listening();

    l.start_listening();
    l.stop_listening();

    l.start_listening();
}

TEST_CASE( "Receive confirmation message test", "[network], [listener]" )
{
    using asio::ip::tcp;
    using namespace testing;

    auto manager_mock = connection_manager_mock {};
    EXPECT_CALL( manager_mock, add_client ).Times( AtLeast( 1 ) );

    constexpr auto port = 5555;
    const auto localhost = std::string { "127.0.0.1" };

    auto l = asio_listener { port, manager_mock };

    auto io_context = asio::io_context {};
    auto resolver = tcp::resolver { io_context };
    auto endpoints = resolver.resolve( localhost, std::to_string( port ) );
    auto socket = tcp::socket { io_context };

    asio::connect( socket, endpoints );

    constexpr auto buffer_size = 128;
    auto buf = std::array<char, buffer_size> { {} };
    auto error = asio::error_code {};

    auto len = static_cast<long long int>(
        socket.read_some( asio::buffer( buf ), error ) );

    spdlog::info( "Read {} bytes", len );
    auto ss = std::stringstream {};
    ss.write( buf.data(), len );
    spdlog::info( "Got: {}", ss.str() );
    REQUIRE( ss.str() == "confirm!" );
    l.stop_listening();
}
