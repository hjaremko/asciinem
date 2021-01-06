#ifndef ASCIINEM_CONSOLE_NCURSES_HPP
#define ASCIINEM_CONSOLE_NCURSES_HPP

#include "server/domain/entity.hpp"

#include <client/controller/user_input.hpp>
#include <ncurses.h>

namespace asciinem::client::view::console
{

struct ncurses
{
    struct raw_window
    {
        raw_window( int y, int x, int height, int width )
            : ptr( ::newwin( height, width, y, x ) )
        {
        }

        raw_window( const raw_window& ) = default;
        raw_window( raw_window&& ) noexcept = default;
        auto operator=( const raw_window& ) -> raw_window& = default;
        auto operator=( raw_window&& ) noexcept -> raw_window& = default;

        ~raw_window()
        {
            ::delwin( ptr );
        }

        void draw_border() const
        {
            ::box( ptr, 0, 0 );
        }

        void refresh() const
        {
            ::wrefresh( ptr );
        }

        void clear() const
        {
            ::werase( ptr );
        }

        void print( int y, int x, const std::string& str ) const
        {
            mvwprintw( ptr, y, x, str.c_str() );
        }

        auto get_center() -> std::pair<int, int>
        {
            auto y { 0 };
            auto x { 0 };
            getmaxyx( ptr, y, x );

            return { x / 2, y / 2 };
        }

        [[nodiscard]] auto get_char() const -> user_input
        {
            return cast_to_user_input( wgetch( ptr ) );
        }

        auto max_height() -> int
        {
            auto y { 0 };
            auto x { 0 };
            getmaxyx( ptr, y, x );

            return y;
        }

        auto max_width() -> int
        {
            [[maybe_unused]] auto y { 0 };
            auto x { 0 };
            getmaxyx( ptr, y, x );

            return x;
        }

        void set_bold() const
        {
            ::wattron( ptr, A_BOLD );
        }

        void set_red() const
        {
            ::wattron( ptr, COLOR_PAIR( 1 ) );
        }

        void set_yellow() const
        {
            ::wattron( ptr, COLOR_PAIR( 2 ) );
        }

        void set_normal() const
        {
            ::wattroff( ptr, COLOR_PAIR( 1 ) );
            ::wattroff( ptr, COLOR_PAIR( 2 ) );
            wattrset( ptr, 0 );
        }

        WINDOW* ptr;
    };

    using window_pointer = std::unique_ptr<raw_window>;

    ncurses()
    {
        initscr();
        timeout( 1 );
        noecho();
        curs_set( 0 );
        ::start_color();
        init_pair( 1, COLOR_RED, COLOR_BLACK );
        init_pair( 2, COLOR_YELLOW, COLOR_BLACK );
    }

    ncurses( const ncurses& ) = default;
    ncurses( ncurses&& ) noexcept = default;
    auto operator=( const ncurses& ) -> ncurses& = default;
    auto operator=( ncurses&& ) noexcept -> ncurses& = default;

    ~ncurses()
    {
        endwin();
    }

    static void clear()
    {
        ::erase();
    }

    static void refresh()
    {
        ::refresh();
    }

    static auto max_height() -> int
    {
        auto y { 0 };
        auto x { 0 };
        getmaxyx( stdscr, y, x );

        return y;
    }

    static auto max_width() -> int
    {
        [[maybe_unused]] auto y { 0 };
        auto x { 0 };
        getmaxyx( stdscr, y, x );

        return x;
    }

    static void print( int y, int x, const std::string& str )
    {
        mvprintw( y, x, str.c_str() );
    }

    static auto make_window( int y, int x, int height, int width )
        -> window_pointer
    {
        return std::make_unique<raw_window>( y, x, height, width );
    }

    static auto get_char() -> user_input
    {
        return cast_to_user_input( wgetch( stdscr ) );
    }
};

} // namespace asciinem::client::view::console

#endif // ASCIINEM_CONSOLE_NCURSES_HPP
