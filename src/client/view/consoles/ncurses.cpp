#include "client/view/consoles/ncurses.hpp"

namespace asciinem::client::view::console
{

void ncurses::initialize()
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

auto ncurses::standard_screen() -> WINDOW*
{
    return stdscr;
}

void ncurses::end()
{
    endwin();
}

void ncurses::destroy_window( WINDOW* win )
{
    ::delwin( win );
}

void ncurses::clear( WINDOW* win )
{
    ::werase( win );
}

void ncurses::refresh( WINDOW* win )
{
    ::wrefresh( win );
}

void ncurses::draw_border( WINDOW* win )
{
    ::box( win, 0, 0 );
}

auto ncurses::max_height( WINDOW* win ) -> int
{
    auto y { 0 };
    auto x { 0 };
    getmaxyx( win, y, x );

    return y;
}

auto ncurses::max_width( WINDOW* win ) -> int
{
    [[maybe_unused]] auto y { 0 };
    auto x { 0 };
    getmaxyx( win, y, x );

    return x;
}

void ncurses::print( int y, int x, const std::string& str )
{
    mvprintw( y, x, str.c_str() );
}

auto ncurses::make_window( int y, int x, int height, int width ) -> WINDOW*
{
    return ::newwin( height, width, y, x );
}

auto ncurses::get_char( WINDOW* win ) -> user_input
{
    return cast_to_user_input( wgetch( win ) );
}

auto ncurses::get_center( WINDOW* win ) -> std::pair<int, int>
{
    auto y { 0 };
    auto x { 0 };
    getmaxyx( win, y, x );

    return { x / 2, y / 2 };
}

void ncurses::set_bold( WINDOW* win )
{
    ::wattron( win, A_BOLD );
}

void ncurses::set_red( WINDOW* win )
{
    ::wattron( win, COLOR_PAIR( 1 ) );
}

void ncurses::set_yellow( WINDOW* win )
{
    ::wattron( win, COLOR_PAIR( 2 ) );
}

void ncurses::set_green( WINDOW* win )
{
    ::wattron( win, COLOR_PAIR( 3 ) );
}

void ncurses::set_blue( WINDOW* win )
{
    ::wattron( win, COLOR_PAIR( 4 ) );
}

void ncurses::set_normal( WINDOW* win )
{
    ::wattroff( win, COLOR_PAIR( 1 ) );
    ::wattroff( win, COLOR_PAIR( 2 ) );
    ::wattroff( win, COLOR_PAIR( 3 ) );
    ::wattroff( win, COLOR_PAIR( 4 ) );
    wattrset( win, 0 );
}

void ncurses::print( WINDOW* win, int y, int x, const std::string& format )
{
    mvwprintw( win, y, x, format.c_str() );
}

void ncurses::move( WINDOW* win, int y, int x )
{
    mvwin( win, y, x );
}

} // namespace asciinem::client::view::console
