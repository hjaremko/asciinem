#ifndef ASCIINEM_MACOS_NCURSES_HPP
#define ASCIINEM_MACOS_NCURSES_HPP

#include "ncurses.hpp"

#include <ncurses.h>

namespace asciinem::client::view::console
{

struct macos_ncurses : public ncurses
{
    static void draw_border(raw_window_ptr win)
    {
        ::wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    }
};

} // namespace asciinem::client::view::console

#endif // ASCIINEM_MACOS_NCURSES_HPP
