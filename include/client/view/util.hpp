#ifndef ASCIINEM_CLIENT_VIEW_UTIL_HPP
#define ASCIINEM_CLIENT_VIEW_UTIL_HPP

#include "client/view/consoles/macos_ncurses.hpp"
#include "client/view/consoles/ncurses.hpp"
#include "client/view/main_window.hpp"

namespace asciinem::client::view
{

using terminal_handler =
#ifdef __APPLE__
    console::macos_ncurses;
#else
    console::ncurses;
#endif

inline auto make_main_window( const std::string& login )
    -> main_window<terminal_handler>
{
    return main_window<terminal_handler> { login };
}

} // namespace asciinem::client::view

#endif // ASCIINEM_CLIENT_VIEW_UTIL_HPP
