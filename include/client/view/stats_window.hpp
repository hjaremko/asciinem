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
        draw_eq( *you );
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
            6,
            4,
            fmt::format( "Gold:    {}",
                         static_cast<double>( you.get_money() ) ) );
        this->raw_window.print(
            7, 4, fmt::format( "Attack:  {}", you.get_attack() ) );
        this->raw_window.print(
            8, 4, fmt::format( "Defence: {}", you.get_defense() ) );
    }

    void draw_bars( const server::domain::player& you ) const
    {
        this->raw_window.print( 10,
                                2,
                                fmt::format( "Health {}/{}",
                                             you.get_health(),
                                             you.get_max_health() ) );
        draw_red_bar(
            11, base::width() - 7, you.get_health(), you.get_max_health() );

        this->raw_window.print(
            12,
            2,
            fmt::format( "Exp {}/{}", you.get_exp(), 100 * you.get_level() ) );
        draw_yellow_bar(
            13, base::width() - 7, you.get_exp(), 100 * you.get_level() );
    }

    void draw_red_bar( int y, int bars, int value, int max ) const
    {
        auto percent = static_cast<double>( value ) / max;
        auto filled_bars = static_cast<unsigned long>( bars * percent );

        this->raw_window.set_red();
        this->raw_window.print(
            y, 4, std::string( static_cast<unsigned long>( bars ), '|' ) );

        this->raw_window.set_bold();
        this->raw_window.print( y, 4, std::string( filled_bars, '|' ) );

        this->raw_window.set_normal();
    }

    void draw_yellow_bar( int y, int bars, int value, int max ) const
    {
        auto percent = static_cast<double>( value ) / max;
        auto filled_bars = static_cast<unsigned long>( bars * percent );

        this->raw_window.set_yellow();
        this->raw_window.print(
            y, 4, std::string( static_cast<unsigned long>( bars ), '|' ) );

        this->raw_window.set_bold();
        this->raw_window.print( y, 4, std::string( filled_bars, '|' ) );

        this->raw_window.set_normal();
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

        this->raw_window.print( 15,
                                2,
                                fmt::format( "Backpack: {}/{}",
                                             bp.size(),
                                             you.get_backpack_capacity() ) );

        int offset = 0;
        for ( const auto& i : bp )
        {
            this->raw_window.print(
                16 + offset, 4, fmt::format( "{} {}", offset, i->get_name() ) );
            offset++;
        }

        if ( you.get_weapon() )
        {
            this->raw_window.print(
                16 + offset + 2,
                4,
                fmt::format( "weapon: {}", you.get_weapon()->get_name() ) );
            offset++;
        }

        if ( you.get_armor(

                 ) )
        {
            this->raw_window.print(
                16 + offset + 3,
                4,
                fmt::format( "armor: {}", you.get_armor()->get_name() ) );
            offset++;
        }
    }
};

} // namespace asciinem::client::view

#endif // ASCIINEM_CLIENT_VIEW_STATS_WINDOW_HPP
