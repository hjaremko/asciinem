#include "client/network/asio_network_module.hpp"
#include "client/util.hpp"
#include "client/view/util.hpp"

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

template <class T>
void init_basic_gui( asciinem::client::network::network_module& net,
                     const std::string& login,
                     asciinem::client::view::main_window<T>& view )
{
    using namespace std::chrono_literals;

    while ( true )
    {
        auto state = asciinem::server::domain::game_state {};
        auto msg = std::string {};

        while ( net.has_message_available() )
        {
            msg = net.poll_message();
        }

        if ( !msg.empty() )
        {
            state = asciinem::server::serializer::deserialize<
                asciinem::server::domain::game_state>( msg );

            view.draw( state );
        }

        auto input = getch();
        refresh();

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

        std::this_thread::sleep_for( 1ms );
    }
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

        // ---------------------------------------------------------------------
        auto view = view::make_main_window( login );
        init_basic_gui( net, login, view );
    }
    catch ( std::exception& e )
    {
        spdlog::error( "Unexpected exception: {}", e.what() );
    }

    return 0;
}
