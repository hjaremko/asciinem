#include "client/view/notify_view.hpp"

namespace asciinem::client::view
{

void notify_view::draw( const server::domain::game_state& state,
                        const std::string& login )
{
    auto you = state.find_player( login );

    if ( you == nullptr )
    {
        return;
    }

    auto notice = state.get_notice();

    if ( !notice.empty() )
    {
        auto border = "+" + std::string( notice.length() + 2, '-' ) + "+";

        raw_window_->print( 1, 1, border );
        raw_window_->print( 2, 1, fmt::format( "| {} |", notice ) );
        raw_window_->print( 3, 1, border );

        raw_window_->refresh();
    }
}

} // namespace asciinem::client::view