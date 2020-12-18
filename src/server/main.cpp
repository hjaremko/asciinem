#include "network/asio_factory.hpp"
#include "network/clock.hpp"
#include "network/interfaces/network_factory.hpp"
#include "network/server_config.hpp"

#include <iostream>

auto main() -> int
{
    using namespace asciinem::server;

    spdlog::default_logger_raw()->set_level( spdlog::level::info );
    spdlog::info( "Asciinem Server starting!" );

    constexpr auto clock_interval = 1500;
    auto clock = network::make_clock<clock_interval>();

    auto network = network::create_network(
        network::default_config, network::asio_factory::instance(), clock );

    constexpr auto dummy_data_amount = 100;
    for ( int i = 1; i <= dummy_data_amount; ++i )
    {
        network->queue_message( std::to_string( i ) );
    }

    std::cin.get();

    spdlog::warn( "Asciinem Server shutting down." );
    return 0;
}
