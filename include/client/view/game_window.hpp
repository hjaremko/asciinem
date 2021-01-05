#ifndef ASCIINEM_GAME_WINDOW_HPP
#define ASCIINEM_GAME_WINDOW_HPP

#include "client/view/interfaces/window.hpp"

#include <utility>

namespace asciinem::client::view
{

template <class Console>
class game_window : public window<Console>
{
public:
    using window<Console>::window;

    auto find_relative_pos( std::pair<int, int> player_pos,
                            std::pair<int, int> entity_pos )
        -> std::pair<int, int>
    {
        auto [ cx, cy ] = this->raw_window.get_center();
        auto [ x, y ] = entity_pos;
        auto [ xp, yp ] = player_pos;
        x += cx - xp;
        y += cy - yp;

        return { x, y };
    }

    void draw( game_state_cr state, const std::string& login ) override
    {
        this->draw_border();
        auto you = state.find_player( login );

        if ( you == nullptr )
        {
            return;
        }

        auto you_pos = you->get_position();

        for ( const auto& e : state.get_entities() )
        {
            if ( e->get_name() != you->get_name() )
            {
                auto pos = find_relative_pos( you_pos, e->get_position() );
                print_entity( e, pos, "\\o/" );
            }
        }

        for ( const auto& e : state.get_monsters() )
        {
            if ( e->get_name() != you->get_name() )
            {
                auto pos = find_relative_pos( you_pos, e->get_position() );
                print_entity( e, pos, "@" );
            }
        }

        print_you( this->raw_window.get_center() );
    }

private:
    void print_entity( const asciinem::server::domain::entity::pointer& e,
                       std::pair<int, int> pos,
                       const std::string& look )
    {
        auto [ x, y ] = pos;

        this->raw_window.print(
            y - 1,
            x - 5,
            fmt::format( "Lv {} {}", e->get_level(), e->get_name() ) );
        //        this->raw_window.print(
        //            y + 1, x - 5, fmt::format( "{}/100", e->get_health() ) );
        this->raw_window.print( y, x, look.c_str() );
    }

    void print_you( std::pair<int, int> pos )
    {
        auto [ x, y ] = pos;
        this->raw_window.print( y, x, "\\o/" );
    }
};

} // namespace asciinem::client::view

#endif // ASCIINEM_GAME_WINDOW_HPP
