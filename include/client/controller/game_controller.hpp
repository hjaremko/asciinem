#ifndef ASCIINEM_SERVER_EVENT_HANDLER_H
#define ASCIINEM_SERVER_EVENT_HANDLER_H

#include <client/network/interfaces/network_module.hpp>
#include <client/view/main_window.hpp>
#include <ncurses.h>
#include <spdlog/spdlog.h>
#include <thread>

namespace asciinem::client
{

template <class Console>
class game_controller
{
public:
    explicit game_controller( asciinem::client::network::network_module& net,
                              view::main_window<Console>& view,
                              const std::string& login )
        : net_( net ), view_( view ), login_( login )
    {
    }

    auto run() -> void
    {
        using namespace std::chrono_literals;

        while ( true )
        {
            fetch_game_state();

            if ( handle_user_input() == view::console::user_input::QUIT )
            {
                break;
            }

            std::this_thread::sleep_for( 1ms );
        }
    }

protected:
    auto fetch_game_state() -> void
    {
        auto state = asciinem::server::domain::game_state {};
        auto msg = std::string {};

        while ( net_.has_message_available() )
        {
            msg = net_.poll_message();
        }

        if ( !msg.empty() )
        {
            state = asciinem::server::serializer::deserialize<
                asciinem::server::domain::game_state>( msg );

            view_.draw( state );
        }
    }

    auto handle_user_input() -> view::console::user_input
    {
        using namespace view::console;

        auto input = Console::get_char();
        Console::refresh();

        if ( input == user_input::QUIT )
        {
            spdlog::info( "Quitting." );
        }
        else if ( input != user_input::INVALID )
        {
            spdlog::trace( "Pressed '{}'", input );
            net_.queue_message( login_ + " " + make_move_request( input ) );
        }

        return input;
    }

    auto make_move_request( view::console::user_input input ) -> std::string
    {
        using namespace view::console;

        switch ( input )
        {
        case user_input::UP:
            return "move_up;";

        case user_input::DOWN:
            return "move_down;";

        case user_input::LEFT:
            return "move_left;";

        case user_input::RIGHT:
            return "move_right;";

        default:
            return "invalid";
        }
    }

private:
    asciinem::client::network::network_module& net_;
    asciinem::client::view::main_window<Console>& view_;
    const std::string& login_;
};

} // namespace asciinem::client
#endif // ASCIINEM_SERVER_EVENT_HANDLER_H
