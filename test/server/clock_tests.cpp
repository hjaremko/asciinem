#include "network/clock.hpp"

#include <catch2/catch.hpp>

using namespace std::chrono_literals;
using namespace asciinem::server::network;
using namespace asciinem::server;

TEST_CASE( "Clock RAII test", "[network], [clock]" )
{
    spdlog::default_logger_raw()->set_level( spdlog::level::debug );
    auto c = network::clock<300> {};

    std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
}

TEST_CASE( "Clock attach test", "[network], [clock]" )
{
    spdlog::default_logger_raw()->set_level( spdlog::level::debug );

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

    spdlog::default_logger_raw()->set_level( spdlog::level::debug );
    auto c = network::clock<100> {};
    auto o = std::make_shared<mock_observer>();

    c.attach( o );

    std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
}

TEST_CASE( "Clock detach test", "[network], [clock]" )
{
    spdlog::default_logger_raw()->set_level( spdlog::level::debug );

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

    spdlog::default_logger_raw()->set_level( spdlog::level::debug );
    auto c = network::clock<100> {};
    auto o = std::make_shared<mock_observer>();
    auto o2 = std::make_shared<mock_observer>();

    c.attach( o );
    c.attach( o2 );
    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
    c.detach( o );
    std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
}
