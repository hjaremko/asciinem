#include "network/asio_listener.hpp"
#include "network/asio_manager.hpp"
#include "network/clock.hpp"
#include "network/message_queue.hpp"

#include <iostream>

auto main() -> int
{
    using namespace asciinem::server;

    spdlog::default_logger_raw()->set_level( spdlog::level::info );
    spdlog::info( "Asciinem Server starting!" );

    constexpr auto clock_interval = 1500;
    constexpr auto dummy_data_amount = 100;
    auto clock = network::clock<clock_interval> {};
    auto dl = std::make_shared<network::message_queue>();
    auto ul = std::make_shared<network::message_queue>();

    for ( int i = 1; i <= dummy_data_amount; ++i )
    {
        ul->push( std::to_string( i ) );
    }

    // todo: extract io context?
    constexpr auto port = 5555;
    auto conman = network::asio_manager { dl, ul, clock };
    auto l = network::asio_listener( port, conman );

    std::cin.get();

    spdlog::warn( "Asciinem Server shutting down." );
    return 0;
}
