#ifndef ASCIINEM_SERVER_GAME_MANAGER_HPP
#define ASCIINEM_SERVER_GAME_MANAGER_HPP

#include "game_state.hpp"
#include "player.hpp"

#include <algorithm>

namespace asciinem::server::domain
{

class game_manager
{
public:
    [[nodiscard]] auto get_state() const -> game_state
    {
        return current_state_;
    }

    void move_player( const std::string& login,
                      const entity::position_type& offset )
    {
        auto player = current_state_.find_player( login );
        auto pos = player->get_position();

        pos.first += offset.first;
        pos.second += offset.second;

        player->set_position( pos );
    }

    void add_player( const player::pointer& player )
    {
        current_state_.get_entities().insert( player );
    }

    void remove_player( const player::pointer& player )
    {
        auto& entities = current_state_.get_entities();

        for ( auto it = entities.begin(); it != entities.end(); )
        {
            if ( ( *it )->get_name() == player->get_name() )
            {
                it = entities.erase( it );
            }
            else
            {
                ++it;
            }
        }
    }

private:
    game_state current_state_;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_GAME_MANAGER_HPP
