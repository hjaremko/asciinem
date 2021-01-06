#include "client/network/asio_network_module.hpp"
#include "client/util.hpp"
#include "client/view/consoles/macos_ncurses.hpp"
#include "client/view/consoles/ncurses.hpp"
#include "client/view/util.hpp"

#include <client/controller/game_controller.hpp>

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
        auto view = view::make_view();
        auto controller =
            game_controller<view::terminal_handler>( net, *view, login );
        controller.run();
    }
    catch ( std::exception& e )
    {
        spdlog::error( "Unexpected exception: {}", e.what() );
    }

    return 0;
}
