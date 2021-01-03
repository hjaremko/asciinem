#ifndef ASCIINEM_CLIENT_VIEW_STATS_WINDOW_HPP
#define ASCIINEM_CLIENT_VIEW_STATS_WINDOW_HPP

#include "client/view/interfaces/window.hpp"

namespace asciinem::client::view
{

template <class Console>
class stats_window : public window<Console>
{
public:
    using pointer = std::unique_ptr<stats_window>;
    using base = window<Console>;
    using window<Console>::window;

    void draw( game_state_cr state, const std::string& login ) override
    {
        base::draw_border();
        auto you = state.find_player( login );

        if ( you == nullptr )
        {
            return;
        }

        draw_stats( *you );
        draw_bars( *you );
        // draw_eq();
    }

private:
    void draw_stats( const server::domain::player& you ) const
    {
        auto [ x, y ] = you.get_position();
        this->raw_window.print(
            2, 2, fmt::format( "{} ({}, {})", you.get_name(), x, y ) );

        this->raw_window.print( 4, 2, "Stats" );
        this->raw_window.print(
            5, 4, fmt::format( "Level:   {}", you.get_level() ) );
        this->raw_window.print(
            6, 4, fmt::format( "Gold:    {}", static_cast<double>( you.get_money() ) ) );
        this->raw_window.print(
            7, 4, fmt::format( "Attack:  {}", you.get_attack() ) );
        this->raw_window.print(
            8, 4, fmt::format( "Defence: {}", you.get_defense() ) );
    }

    void draw_bars( const server::domain::player& you ) const
    {
        const auto max = 100;

        this->raw_window.print(
            10, 2, fmt::format( "Health {}/{}", you.get_health(), max ) );
        draw_bar( 11, base::width() - 7, you.get_health(), max );

        const auto max_exp = 100;

        this->raw_window.print(
            12, 2, fmt::format( "Exp {}/{}", you.get_level(), max_exp ) );
        draw_bar( 13, base::width() - 7, you.get_health(), max_exp );
    }

    void draw_bar( int y, int bars, int value, int max ) const
    {
        auto percent = static_cast<double>( value ) / max;
        auto filled_bars = static_cast<unsigned long>( bars * percent );

        this->raw_window.print(
            y, 4, std::string( static_cast<unsigned long>( bars ), '.' ) );
        this->raw_window.print( y, 4, std::string( filled_bars, '|' ) );
    }
};

} // namespace asciinem::client::view

#endif // ASCIINEM_CLIENT_VIEW_STATS_WINDOW_HPP
