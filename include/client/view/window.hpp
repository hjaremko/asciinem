#ifndef ASCIINEM_CLIENT_VIEW_MAIN_WINDOW_HPP
#define ASCIINEM_CLIENT_VIEW_MAIN_WINDOW_HPP

#include "client/view/interfaces/console_window.hpp"
#include "client/view/interfaces/widget.hpp"

namespace asciinem::client::view
{

class window : public widget
{
public:
    explicit window(console_window::pointer raw_window)
        : raw_window_(std::move(raw_window))
    {
    }

    void add_widget(int y, int x, widget::pointer w) override
    {
        w->move(y, x);
        widgets_.emplace_back(std::move(w));
    }

    void draw(game_state_cr state, const std::string& login) override
    {
        for (auto& w : widgets_)
        {
            w->draw(state, login);
        }
    }

    void move(int y, int x) override
    {
        raw_window_->move(y, x);

        for (auto& w : widgets_)
        {
            w->move(y, x);
        }
    }

protected:
    console_window::pointer raw_window_;
    std::vector<widget::pointer> widgets_;
};

} // namespace asciinem::client::view

#endif // ASCIINEM_CLIENT_VIEW_MAIN_WINDOW_HPP
