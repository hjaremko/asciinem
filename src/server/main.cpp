#include "network/asio_listener.hpp"
#include "network/asio_manager.hpp"
#include "network/message_queue.hpp"

#include <iostream>

auto main() -> int
{
    using namespace asciinem::server;

    spdlog::default_logger_raw()->set_level( spdlog::level::debug );

    spdlog::info( "Asciinem Server starting!" );

    auto dl = std::make_shared<network::message_queue>();
    auto ul = std::make_shared<network::message_queue>();

    // todo: io context in ptr?
    constexpr auto port = 5555;
    auto conman = network::asio_manager { dl, ul };
    auto l = network::asio_listener( port, conman );

    std::cin.get();

    spdlog::warn( "Asciinem Server shutting down." );
    return 0;
}
