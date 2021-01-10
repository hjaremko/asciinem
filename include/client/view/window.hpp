#ifndef ASCIINEM_CLIENT_VIEW_MAIN_WINDOW_HPP
#define ASCIINEM_CLIENT_VIEW_MAIN_WINDOW_HPP

#include "client/view/interfaces/console_window.hpp"
#include "client/view/interfaces/widget.hpp"

namespace asciinem::client::view
{

class window : public widget
{
public:
    explicit window( console_window::pointer raw_window );

    void add_widget( int y, int x, widget::pointer w ) override;
    void draw( game_state_cr state, const std::string& login ) override;
    void move( int y, int x ) override;

protected:
    console_window::pointer raw_window_;
    std::vector<widget::pointer> widgets_;
};

} // namespace asciinem::client::view

#endif // ASCIINEM_CLIENT_VIEW_MAIN_WINDOW_HPP
