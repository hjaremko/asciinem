#include "client/view/game_view.hpp"

namespace asciinem::client::view
{

void game_view::draw( const server::domain::game_state& state,
                      const std::string& login )
{
    auto you = state.find_player( login );

    if ( you == nullptr )
    {
        return;
    }

    raw_window_->clear();

    auto you_pos = you->get_position();

    auto m = state.get_map();
    auto map_pos = find_relative_pos( you_pos, { 0, 0 } );
    int i = 0;
    for ( const auto& l : m )
    {
        for ( auto j = 0UL; j < l.size(); ++j )
        {
            auto c = l[ j ];

            if ( c == '#' )
            {
                raw_window_->set_green();
            }

            if ( c == '@' )
            {
                raw_window_->set_blue();
            }

            raw_window_->print( map_pos.second + i,
                                map_pos.first + static_cast<int>( j ),
                                std::string { c } );
            raw_window_->set_normal();
        }
        ++i;
    }

    for ( const auto& e : state.get_entities() )
    {
        if ( e->get_name() != you->get_name() )
        {
            auto pos = find_relative_pos( you_pos, e->get_position() );
            print_entity( e, pos, e->get_shape() );
        }
    }

    for ( const auto& e : state.get_monsters() )
    {
        if ( e->get_name() != you->get_name() )
        {
            auto pos = find_relative_pos( you_pos, e->get_position() );
            print_entity( e, pos, e->get_shape() );
        }
    }

    auto [ x, y ] = raw_window_->get_center();
    this->raw_window_->print( y, x, you->get_shape() );

    raw_window_->draw_border();
    raw_window_->refresh();
    window::draw( state, login );
}

auto game_view::find_relative_pos( std::pair<int, int> player_pos,
                                   std::pair<int, int> entity_pos )
    -> std::pair<int, int>
{
    auto [ cx, cy ] = raw_window_->get_center();
    auto [ x, y ] = entity_pos;
    auto [ xp, yp ] = player_pos;
    x += cx - xp;
    y += cy - yp;

    return { x, y };
}

void game_view::print_entity( const server::domain::entity::pointer& e,
                              std::pair<int, int> pos,
                              const std::string& look )
{
    auto [ x, y ] = pos;

    raw_window_->print(
        y - 1,
        x - 5,
        fmt::format( "Lv {} {}", e->get_level(), e->get_name() ) );

    raw_window_->set_yellow();
    raw_window_->print( y, x, look );
    raw_window_->set_normal();
}

} // namespace asciinem::client::view
