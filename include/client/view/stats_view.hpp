#ifndef ASCIINEM_CLIENT_VIEW_STATS_WINDOW_HPP
#define ASCIINEM_CLIENT_VIEW_STATS_WINDOW_HPP

#include "client/view/window.hpp"

namespace asciinem::client::view
{

class stats_view : public window
{
public:
    using window::window;

    void draw( const server::domain::game_state& state,
               const std::string& login ) override;

private:
    void draw_stats( const server::domain::player& you ) const;
    void draw_bars( const server::domain::player& you ) const;
    void draw_red_bar( int y, int bars, int value, int max ) const;
    void draw_yellow_bar( int y, int bars, int value, int max ) const;
    void draw_bar( int y, int bars, int value, int max ) const;
    void draw_eq( const server::domain::player& you ) const;
};

} // namespace asciinem::client::view

#endif // ASCIINEM_CLIENT_VIEW_STATS_WINDOW_HPP
