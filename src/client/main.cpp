#include "client/network/asio_network_module.hpp"
#include "client/util.hpp"

//#include <ncurses.h>
#include <iostream>
#include <spdlog/spdlog.h>

auto main( int argc, char** argv ) -> int
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

    auto cli_options_result = parse_command_line( argc, argv );
    auto log_level = get_log_level( cli_options_result );
    auto server_port = get_port( cli_options_result );
    auto server_ip = get_ip( cli_options_result );
    auto login = get_login( cli_options_result );

    spdlog::default_logger_raw()->set_level( log_level );

    auto net = network::asio_network_module {};

    net.establish( server_ip, server_port, login );

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
