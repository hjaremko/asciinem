#include "client/network/asio_network_module.hpp"
#include "client/util.hpp"
#include "server/domain/game_state.hpp"
#include "server/serializer.hpp"

#include <iostream>
#include <ncurses.h>

auto make_move_request( char input ) -> std::string
{
    if ( input == 'w' )
    {
        return "move_up;";
    }

    if ( input == 's' )
    {
        return "move_down;";
    }

    if ( input == 'a' )
    {
        return "move_left;";
    }

    if ( input == 'd' )
    {
        return "move_right;";
    }

    return "invalid";
}

void init_basic_gui( asciinem::client::network::network_module& net,
                     const std::string& login )
{
    using namespace std::chrono_literals;

    initscr();
    timeout( 1 );
    noecho();

    while ( true )
    {
        while ( net.has_message_available() )
        {
            auto msg = net.poll_message();
            auto state = asciinem::server::serializer::deserialize<
                asciinem::server::domain::game_state>( msg );

            clear();

            for ( auto [ name, pos ] : state.players_positions_ )
            {
                mvprintw( pos.first - 1, pos.second, name.c_str() );
                mvprintw( pos.first, pos.second, "\\o/" );
            }
        }
        refresh();

        auto input = getch();

        if ( input == 'q' )
        {
            spdlog::info( "Quitting." );
            break;
        }

        if ( input != ERR )
        {
            spdlog::trace( "Pressed '{}'", input );
            net.queue_message(
                login + " " + make_move_request( static_cast<char>( input ) ) );
        }

        std::this_thread::sleep_for( 2ms );
    }

    endwin();
}

auto main( int argc, char** argv ) -> int
{
    using namespace asciinem::client;

    try
    {
        auto cli_options_result = parse_command_line( argc, argv );
        auto log_level = get_log_level( cli_options_result );
        auto server_port = get_port( cli_options_result );
        auto server_ip = get_ip( cli_options_result );
        auto login = get_login( cli_options_result );

        spdlog::default_logger_raw()->set_level( log_level );

        auto net = network::asio_network_module {};
        net.establish( server_ip, server_port, login );

        // -----------------------------------------------------------------------
        init_basic_gui( net, login );
    }
    catch ( std::exception& e )
    {
        spdlog::error( "Unexpected exception: {}", e.what() );
    }

    return 0;
}
