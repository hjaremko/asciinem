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
               const std::string& login ) override
    {
        raw_window_->clear();
        raw_window_->draw_border();
        auto you = state.find_player( login );

        if ( you == nullptr )
        {
            return;
        }

        draw_stats( *you );
        draw_bars( *you );
        draw_eq( *you );
        raw_window_->refresh();
    }

private:
    void draw_stats( const server::domain::player& you ) const
    {
        auto [ x, y ] = you.get_position();
        raw_window_->print(
            2, 2, fmt::format( "{} ({}, {})", you.get_name(), x, y ) );

        raw_window_->print( 4, 2, "Stats" );
        raw_window_->print(
            5, 4, fmt::format( "Level:   {}", you.get_level() ) );
        raw_window_->print(
            6,
            4,
            fmt::format( "Gold:    {}",
                         static_cast<double>( you.get_money() ) ) );
        raw_window_->print(
            7, 4, fmt::format( "Attack:  {}", you.get_attack() ) );
        raw_window_->print(
            8, 4, fmt::format( "Defence: {}", you.get_defense() ) );
    }

    void draw_bars( const server::domain::player& you ) const
    {
        raw_window_->print( 10,
                            2,
                            fmt::format( "Health {}/{}",
                                         you.get_health(),
                                         you.get_max_health() ) );
        draw_red_bar( 11,
                      raw_window_->max_width() - 7,
                      you.get_health(),
                      you.get_max_health() );

        const auto max_exp = 100 * you.get_level();
        raw_window_->print(
            12, 2, fmt::format( "Exp {}/{}", you.get_exp(), max_exp ) );
        draw_yellow_bar(
            13, raw_window_->max_width() - 7, you.get_exp(), max_exp );
    }

    void draw_red_bar( int y, int bars, int value, int max ) const
    {
        raw_window_->set_red();
        draw_bar( y, bars, value, max );
        raw_window_->set_normal();
    }

    void draw_yellow_bar( int y, int bars, int value, int max ) const
    {
        raw_window_->set_yellow();
        draw_bar( y, bars, value, max );
        raw_window_->set_normal();
    }

    void draw_bar( int y, int bars, int value, int max ) const
    {
        auto percent = static_cast<double>( value ) / max;
        auto filled_bars = static_cast<unsigned long>( bars * percent );

        raw_window_->print(
            y, 4, std::string( static_cast<unsigned long>( bars ), '|' ) );

        raw_window_->set_bold();
        raw_window_->print( y, 4, std::string( filled_bars, '|' ) );
    }

    void draw_eq( const server::domain::player& you ) const
    {
        auto bp = std::vector<server::domain::item::pointer> {};

        for ( const auto& p : you.get_backpack() )
        {
            bp.push_back( p );
        }

        std::sort( bp.begin(), bp.end(), []( auto a, auto b ) {
            return a->get_name() < b->get_name();
        } );

        raw_window_->print( 15,
                            2,
                            fmt::format( "Backpack: {}/{}",
                                         bp.size(),
                                         you.get_backpack_capacity() ) );

        int offset = 0;
        for ( const auto& i : bp )
        {
            raw_window_->print(
                16 + offset, 4, fmt::format( "{} {}", offset, i->get_name() ) );
            offset++;
        }

        if ( you.get_weapon() )
        {
            raw_window_->print(
                16 + offset + 2,
                4,
                fmt::format( "weapon: {}", you.get_weapon()->get_name() ) );
            offset++;
        }

        if ( you.get_armor(

                 ) )
        {
            raw_window_->print(
                16 + offset + 3,
                4,
                fmt::format( "armor: {}", you.get_armor()->get_name() ) );
            offset++;
        }
    }
};

} // namespace asciinem::client::view

#endif // ASCIINEM_CLIENT_VIEW_STATS_WINDOW_HPP
