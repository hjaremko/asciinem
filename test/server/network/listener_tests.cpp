#include "mocks/connection_manager_mock.hpp"
#include "server/network/asio_listener.hpp"

#include <catch2/catch.hpp>

using namespace std::chrono_literals;
using namespace asciinem::server::network;

TEST_CASE( "Listener start/stop test", "[network], [listener]" )
{
    auto manager_mock = std::make_shared<connection_manager_mock>();

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

    spdlog::default_logger_raw()->set_level( spdlog::level::debug );

    auto manager_mock = std::make_shared<connection_manager_mock>();
    EXPECT_CALL( *manager_mock, add_client ).Times( AtLeast( 1 ) );

    constexpr auto port = 5555;
    const auto localhost = std::string { "127.0.0.1" };

    auto l = asio_listener { port, manager_mock };

    auto io_context = asio::io_context {};
    auto client = make_connection( io_context, localhost, port, "client" );
    auto actual = client->receive_data();
    actual.pop_back();
    const auto* expected = "confirm!";

    client->disconnect();

    REQUIRE( actual == expected );
    l.stop_listening();
}
