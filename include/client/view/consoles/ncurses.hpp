#ifndef ASCIINEM_CONSOLE_NCURSES_HPP
#define ASCIINEM_CONSOLE_NCURSES_HPP

#include "client/controller/user_input.hpp"

#include <ncurses.h>

namespace asciinem::client::view::console
{

struct ncurses
{
    using raw_window = WINDOW;
    using raw_window_ptr = raw_window*;

    static void initialize()
    {
        initscr();
        timeout( 1 );
        noecho();
        curs_set( 0 );
        ::start_color();
        init_pair( 1, COLOR_RED, COLOR_BLACK );
        init_pair( 2, COLOR_YELLOW, COLOR_BLACK );
        init_pair( 3, COLOR_GREEN, COLOR_BLACK );
        init_pair( 4, COLOR_BLUE, COLOR_BLACK );
    }

    static auto standard_screen() -> raw_window_ptr
    {
        return stdscr;
    }

    static void end()
    {
        endwin();
    }

    static void destroy_window( raw_window_ptr win )
    {
        ::delwin( win );
    }

    static void clear( raw_window_ptr win )
    {
        ::werase( win );
    }

    static void refresh( raw_window_ptr win )
    {
        ::wrefresh( win );
    }

    static void draw_border( raw_window_ptr win )
    {
        ::box( win, 0, 0 );
    }

    static auto max_height( raw_window_ptr win ) -> int
    {
        auto y { 0 };
        auto x { 0 };
        getmaxyx( win, y, x );

        return y;
    }

    static auto max_width( raw_window_ptr win ) -> int
    {
        [[maybe_unused]] auto y { 0 };
        auto x { 0 };
        getmaxyx( win, y, x );

        return x;
    }

    static void print( int y, int x, const std::string& str )
    {
        mvprintw( y, x, "%s", str.c_str() );
    }

    static auto make_window( int y, int x, int height, int width )
        -> raw_window_ptr
    {
        return ::newwin( height, width, y, x );
    }

    static auto get_char( raw_window_ptr win ) -> user_input
    {
        return cast_to_user_input( wgetch( win ) );
    }

    static auto get_center( raw_window_ptr win ) -> std::pair<int, int>
    {
        auto y { 0 };
        auto x { 0 };
        getmaxyx( win, y, x );

        return { x / 2, y / 2 };
    }

    static void set_bold( raw_window_ptr win )
    {
        ::wattron( win, A_BOLD );
    }

    static void set_red( raw_window_ptr win )
    {
        ::wattron( win, COLOR_PAIR( 1 ) );
    }

    static void set_yellow( raw_window_ptr win )
    {
        ::wattron( win, COLOR_PAIR( 2 ) );
    }

    static void set_green( raw_window_ptr win )
    {
        ::wattron( win, COLOR_PAIR( 3 ) );
    }

    static void set_blue( raw_window_ptr win )
    {
        ::wattron( win, COLOR_PAIR( 4 ) );
    }

    static void set_normal( raw_window_ptr win )
    {
        ::wattroff( win, COLOR_PAIR( 1 ) );
        ::wattroff( win, COLOR_PAIR( 2 ) );
        ::wattroff( win, COLOR_PAIR( 3 ) );
        ::wattroff( win, COLOR_PAIR( 4 ) );
        wattrset( win, 0 );
    }

    static void
    print( raw_window_ptr win, int y, int x, const std::string& format )
    {
        mvwprintw( win, y, x, "%s", format.c_str() );
    }

    static void move( raw_window_ptr win, int y, int x )
    {
        mvwin( win, y, x );
    }
};

} // namespace asciinem::client::view::console

#endif // ASCIINEM_CONSOLE_NCURSES_HPP
