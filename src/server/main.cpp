#include "server/network/asio_listener.hpp"
#include "server/network/asio_manager.hpp"
#include "server/network/clock.hpp"
#include "server/network/message_queue.hpp"
#include "server/network/asio_factory.hpp"
#include "server/network/clock.hpp"
#include "server/util.hpp"

#include <iostream>

auto main( int argc, char** argv ) -> int
{
    using namespace asciinem::server;

    auto cli_options_result = parse_command_line( argc, argv );
    auto log_level = get_log_level( cli_options_result );
    auto port = get_port( cli_options_result );

    spdlog::default_logger_raw()->set_level( log_level );
    spdlog::info( "Asciinem Server starting!" );

    constexpr auto clock_interval = 1500;
    auto clock = network::make_clock<clock_interval>();

    auto network = network::create_network(
        { port }, network::asio_factory::instance(), clock );

    constexpr auto dummy_data_amount = 100;
    for ( int i = 1; i <= dummy_data_amount; ++i )
    {
        network->queue_message( std::to_string( i ) );
    }

    std::cin.get();

    spdlog::warn( "Asciinem Server shutting down." );
    return 0;
}
