#include "server/domain/collision_checker.hpp"
using namespace asciinem::server::domain;

auto collision_checker::check_collision(
    const player::position_type& player_position,
    const monster::position_type& monster_position ) -> bool
{
    return player_position == monster_position;
}

auto collision_checker::check_collision(
    const player::position_type& player_position, const location& location )
    -> bool
{
    return location.get_collision_map()[ player_position.first ]   // NOLINT
                                       [ player_position.second ]; // NOLINT
}
