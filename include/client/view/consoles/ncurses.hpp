#ifndef ASCIINEM_CONSOLE_NCURSES_HPP
#define ASCIINEM_CONSOLE_NCURSES_HPP

#include "client/controller/user_input.hpp"

#include <curses.h>
#include <string>
#include <utility>

namespace asciinem::client::view::console
{

struct ncurses
{
    using raw_window = WINDOW;
    using raw_window_ptr = raw_window*;

    static void initialize();
    static auto standard_screen() -> raw_window_ptr;
    static void end();
    static void destroy_window( raw_window_ptr win );
    static void clear( raw_window_ptr win );
    static void refresh( raw_window_ptr win );
    static void draw_border( raw_window_ptr win );
    static auto max_height( raw_window_ptr win ) -> int;
    static auto max_width( raw_window_ptr win ) -> int;
    static void print( int y, int x, const std::string& str );
    static auto make_window( int y, int x, int height, int width )
        -> raw_window_ptr;
    static auto get_char( raw_window_ptr win ) -> user_input;
    static auto get_center( raw_window_ptr win ) -> std::pair<int, int>;
    static void set_bold( raw_window_ptr win );
    static void set_red( raw_window_ptr win );
    static void set_yellow( raw_window_ptr win );
    static void set_green( raw_window_ptr win );
    static void set_blue( raw_window_ptr win );
    static void set_normal( raw_window_ptr win );
    static void
    print( raw_window_ptr win, int y, int x, const std::string& format );
    static void move( raw_window_ptr win, int y, int x );
};

} // namespace asciinem::client::view::console

#endif // ASCIINEM_CONSOLE_NCURSES_HPP
