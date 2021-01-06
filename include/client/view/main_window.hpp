#ifndef ASCIINEM_CLIENT_VIEW_MAIN_WINDOW_HPP
#define ASCIINEM_CLIENT_VIEW_MAIN_WINDOW_HPP

#include "client/view/game_window.hpp"
#include "client/view/notice_window.hpp"
#include "client/view/stats_window.hpp"

namespace asciinem::client::view
{

template <class Console>
class main_window : public Console
{
public:
    explicit main_window( std::string login )
        : Console(),
          game_window_( std::make_unique<game_window<Console>>(
              1, 1, Console::max_height() - 2, Console::max_width() - 35 ) ),
          stats_window_( std::make_unique<stats_window<Console>>(
              1, Console::max_width() - 30, Console::max_height() - 2, 30 ) ),
          notice_window_(
              std::make_unique<notice_window<Console>>( 2, 2, 5, 60 ) ),
          login_( std::move( login ) )
    {
    }

    void draw( game_state_cr state )
    {
        game_window_->clear();
        game_window_->draw( state, login_ );
        game_window_->refresh();

        stats_window_->clear();
        stats_window_->draw( state, login_ );
        stats_window_->refresh();

        notice_window_->draw( state, login_ );
    }

private:
    typename window<Console>::pointer game_window_;
    typename window<Console>::pointer stats_window_;
    typename window<Console>::pointer notice_window_;
    std::string login_;
};

} // namespace asciinem::client::view

#endif // ASCIINEM_CLIENT_VIEW_MAIN_WINDOW_HPP
