#ifndef ASCIINEM_NCURSES_MAIN_WINDOW_HPP
#define ASCIINEM_NCURSES_MAIN_WINDOW_HPP

#include "ncurses_window.hpp"

namespace asciinem::client::view
{

template <class Curses>
class ncurses_main_window : public ncurses_window<Curses>
{
public:
    ncurses_main_window()
        : ncurses_window<Curses>(
              ( Curses::initialize(), Curses::standard_screen() ) )
    {
    }

    ~ncurses_main_window() override
    {
        Curses::end();
    }
};

} // namespace asciinem::client::view

#endif // ASCIINEM_NCURSES_MAIN_WINDOW_HPP
