#include "network/clock.hpp"

#include <catch2/catch.hpp>

using namespace std::chrono_literals;
using namespace asciinem::server::network;
using namespace asciinem::server;

namespace
{

class mock_observer : public network::observer
{
public:
    void update() override
    {
        spdlog::debug( "Mock got tick!" );
    }

    auto name() -> std::string override
    {
        return "mock observer";
    }
};

} // namespace

TEST_CASE( "Clock RAII test", "[network], [clock]" )
{
    spdlog::default_logger_raw()->set_level( spdlog::level::debug );
    constexpr auto clock_interval = 300;
    constexpr auto clock_run_duration = 1000;

    auto c = network::clock<clock_interval> {};

    std::this_thread::sleep_for(
        std::chrono::milliseconds( clock_run_duration ) );

    c.notify();
}

TEST_CASE( "Clock attach test", "[network], [clock]" )
{
    spdlog::default_logger_raw()->set_level( spdlog::level::debug );
    constexpr auto clock_interval = 100;
    constexpr auto clock_run_duration = 1000;

    auto c = network::clock<clock_interval> {};
    auto o = std::make_shared<mock_observer>();

    c.attach( o );

    std::this_thread::sleep_for(
        std::chrono::milliseconds( clock_run_duration ) );
}

TEST_CASE( "Clock detach test", "[network], [clock]" )
{
    spdlog::default_logger_raw()->set_level( spdlog::level::debug );
    constexpr auto clock_interval = 100;
    constexpr auto clock_run_duration = 500;

    auto c = network::clock<clock_interval> {};
    auto o = std::make_shared<mock_observer>();
    auto o2 = std::make_shared<mock_observer>();

    c.attach( o );
    c.attach( o2 );
    std::this_thread::sleep_for(
        std::chrono::milliseconds( clock_run_duration ) );
    c.detach( o );
    std::this_thread::sleep_for(
        std::chrono::milliseconds( clock_run_duration ) );
}
