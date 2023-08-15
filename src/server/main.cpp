#include "server/network/asio_factory.hpp"
#include "server/network/clock.hpp"
#include "server/network_service_mediator.hpp"
#include "server/util.hpp"

#include <iostream>

using namespace asciinem;

auto main(int argc, char** argv) -> int
{
    using namespace asciinem::server;

    try
    {
        auto cli_options_result = parse_command_line(argc, argv);
        auto log_level = get_log_level(cli_options_result);
        auto port = get_port(cli_options_result);

        spdlog::default_logger_raw()->set_level(log_level);
        spdlog::info("Asciinem Server starting!");

        constexpr auto clock_interval = 10;
        auto clock = network::make_clock<clock_interval>();

        auto network = network::create_network(
            {port},
            network::asio_factory::instance(),
            clock
        );

        auto gm = domain::game_manager{};
        auto gs = service::game_service{gm};

        auto mediator = network_service_mediator{*clock, *network, gs};

        std::cin.get();

        spdlog::warn("Asciinem Server shutting down.");
    }
    catch (std::exception& e)
    {
        spdlog::error("Unexpected server error: {}", e.what());
    }

    return 0;
}
