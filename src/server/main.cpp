#include "server/network/asio_factory.hpp"
// #include "server/network_service_mediator.hpp"
// #include "server/network/clock.hpp"
#include "server/util.hpp"

#include <asio/io_context.hpp>
#include <asio/signal_set.hpp>

#include <thread>

using namespace asciinem;

auto main(int argc, char** argv) -> int
{
    using namespace asciinem::server;

    asio::io_context io_context;
    asio::signal_set signals(io_context, SIGINT, SIGTERM, SIGPIPE);

    signals.async_wait(
        [&io_context](const auto& /*ec*/, int signal)
        {
            spdlog::warn("Asciinem Server shutting down.");
            io_context.stop();
        }
    );

    try
    {
        auto cli_options_result = parse_command_line(argc, argv);
        auto log_level = get_log_level(cli_options_result);
        auto port = get_port(cli_options_result);

        spdlog::default_logger_raw()->set_level(log_level);
        spdlog::info("Asciinem Server starting!");

        //        constexpr auto clock_interval = 10;
        //        auto clock = network::make_clock<clock_interval>();

        auto network = network::create_network(
            io_context,
            {port},
            //            clock
        );
        //
        //        auto gm = domain::game_manager{};
        //        auto gs = service::game_service{gm};
        //
        //        auto mediator = network_service_mediator{*clock, *network,
        //        gs};

        //        std::cin.get();
    }
    catch (std::exception& e)
    {
        spdlog::error("Unexpected server error: {}", e.what());
    }

    const auto cores = std::thread::hardware_concurrency();
    spdlog::info("Starting on {} threads.", cores);


    std::vector<std::jthread> threads;
    threads.reserve(cores - 1);
    for (auto i = 0u; i < cores - 1; ++i)
    {
        threads.emplace_back(
            [&io_context]
            {
                io_context.run();
            }
        );
    }

    io_context.run();

    return 0;
}
