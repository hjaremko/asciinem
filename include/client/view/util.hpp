#ifndef ASCIINEM_CLIENT_VIEW_UTIL_HPP
#define ASCIINEM_CLIENT_VIEW_UTIL_HPP

#include "client/view/consoles/macos_ncurses.hpp"
#include "client/view/consoles/ncurses.hpp"
#include "client/view/game_view.hpp"
#include "client/view/interfaces/widget.hpp"
#include "client/view/notify_view.hpp"
#include "client/view/stats_view.hpp"

namespace asciinem::client::view
{

using terminal_handler =
#ifdef __APPLE__
    console::macos_ncurses;
#else
    console::ncurses;
#endif

inline auto make_main_window() -> widget::pointer
{
    return std::make_unique<window>(
        std::make_unique<ncurses_main_window<terminal_handler>>() );
}

inline auto make_game_window( int height, int width ) -> widget::pointer
{
    return std::make_unique<game_view>(
        std::make_unique<ncurses_window<terminal_handler>>(
            0, 0, height, width ) );
}

inline auto make_stats_window( int height, int width ) -> widget::pointer
{
    return std::make_unique<stats_view>(
        std::make_unique<ncurses_window<terminal_handler>>(
            0, 0, height, width ) );
}

inline auto make_notify_window( int height, int width ) -> widget::pointer
{
    return std::make_unique<notify_view>(
        std::make_unique<ncurses_window<terminal_handler>>(
            0, 0, height, width ) );
}

inline auto make_view() -> widget::pointer
{
    auto main_win = make_main_window();

    auto max_height =
        terminal_handler::max_height( terminal_handler::standard_screen() );
    auto max_width =
        terminal_handler::max_width( terminal_handler::standard_screen() );

    auto game_win = make_game_window( max_height - 2, max_width - 35 );
    auto stats_win = make_stats_window( max_height - 2, 33 );
    auto notify_win = make_notify_window( 5, 60 );

    game_win->add_widget( 1, 1, std::move( notify_win ) );
    main_win->add_widget( 1, 1, std::move( game_win ) );
    main_win->add_widget( 1, max_width - 33, std::move( stats_win ) );

    return main_win;
}

} // namespace asciinem::client::view

#endif // ASCIINEM_CLIENT_VIEW_UTIL_HPP
