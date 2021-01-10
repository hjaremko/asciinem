#include "client/view/window.hpp"

namespace asciinem::client::view
{

window::window( console_window::pointer raw_window )
    : raw_window_( std::move( raw_window ) )
{
}

void window::add_widget( int y, int x, widget::pointer w )
{
    w->move( y, x );
    widgets_.emplace_back( std::move( w ) );
}

void window::draw( const server::domain::game_state& state,
                   const std::string& login )
{
    for ( auto& w : widgets_ )
    {
        w->draw( state, login );
    }
}

void window::move( int y, int x )
{
    raw_window_->move( y, x );

    for ( auto& w : widgets_ )
    {
        w->move( y, x );
    }
}

} // namespace asciinem::client::view
