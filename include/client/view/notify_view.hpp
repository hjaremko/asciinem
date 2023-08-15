#ifndef ASCIINEM_SERVER_NOTICE_WINDOW_H
#define ASCIINEM_SERVER_NOTICE_WINDOW_H

#include "client/view/window.hpp"

namespace asciinem::client::view
{

class notify_view : public window
{
public:
    using window::window;

    void draw(const server::domain::game_state& state, const std::string& login)
        override
    {
        auto you = state.find_player(login);

        if (you == nullptr)
        {
            return;
        }

        auto notice = state.get_notice();

        if (!notice.empty())
        {
            auto border = "+" + std::string(notice.length() + 2, '-') + "+";

            raw_window_->print(1, 1, border);
            raw_window_->print(2, 1, fmt::format("| {} |", notice));
            raw_window_->print(3, 1, border);

            raw_window_->refresh();
        }
    }
};

} // namespace asciinem::client::view

#endif // ASCIINEM_SERVER_NOTICE_WINDOW_H
