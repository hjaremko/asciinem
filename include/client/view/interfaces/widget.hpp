#ifndef ASCIINEM_CLIENT_WIDGET_HPP
#define ASCIINEM_CLIENT_WIDGET_HPP

#include "console_window.hpp"

namespace asciinem::client::view
{

using game_state_cr = const server::domain::game_state&;

// composite
class widget
{
public:
    using pointer = std::unique_ptr<widget>;

    widget() = default;
    widget(const widget&) = default;
    widget(widget&&) noexcept = default;
    auto operator=(const widget&) -> widget& = default;
    auto operator=(widget&&) noexcept -> widget& = default;
    virtual ~widget() = default;

    virtual void draw(game_state_cr, const std::string&){};
    virtual void add_widget(int, int, widget::pointer){};
    virtual void move(int, int){};
};

} // namespace asciinem::client::view

#endif // ASCIINEM_CLIENT_WIDGET_HPP
