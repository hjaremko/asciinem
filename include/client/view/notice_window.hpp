#ifndef ASCIINEM_SERVER_NOTICE_WINDOW_H
#define ASCIINEM_SERVER_NOTICE_WINDOW_H

#include "client/view/interfaces/window.hpp"

namespace asciinem::client::view
{

template <class Console>
class notice_window : public window<Console>
{
public:
    using pointer = std::unique_ptr<notice_window>;
    using base = window<Console>;
    using window<Console>::window;

    void draw( game_state_cr state, const std::string& login ) override
    {
        auto you = state.find_player( login );

        if ( you == nullptr )
        {
            return;
        }

        auto notice = state.get_notice();

        if ( !notice.empty() )
        {
            this->clear();

            auto border = "+" + std::string( notice.length() + 2, '-' ) + "+";

            this->raw_window.print( 1, 1, border );
            this->raw_window.print( 2, 1, fmt::format( "| {} |", notice ) );
            this->raw_window.print( 3, 1, border );

            this->refresh();
        }
    }
};

} // namespace asciinem::client::view

#endif // ASCIINEM_SERVER_NOTICE_WINDOW_H
