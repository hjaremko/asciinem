#include "client/network/asio_network_module.hpp"

//#include <ncurses.h>
#include <iostream>
#include <spdlog/spdlog.h>

auto main() -> int
{
    // todo: text interface
    //    initscr();
    //    printw( "Hello World !!!" );
    //    // todo: if macos
    //    refresh();
    //    getch();
    //    endwin();

    using namespace asciinem::client;
    using namespace std::chrono_literals;

    spdlog::default_logger_raw()->set_level( spdlog::level::debug );

    auto net = network::asio_network_module {};

    constexpr auto port = 5555;
    const auto server_ip = std::string { "localhost" };

    while ( !net.establish( server_ip, port ) )
    {
        std::this_thread::sleep_for( 1s );
    }

    auto input = std::string {};
    while ( std::cin >> input )
    {
        if ( input == "q" )
        {
            break;
        }

        net.queue_message( input );
    }

    return 0;
}
