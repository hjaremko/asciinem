#include "server/domain/fight_manager.hpp"

#include "server/domain/monster.hpp"
#include "server/domain/player.hpp"

#include <spdlog/spdlog.h>

namespace asciinem::server::domain
{

void fight_manager::fight( player& player, monster& monster )
{
    while ( !player.is_dead() && !monster.is_dead() )
    {
        spdlog::trace( "Player health = {}, monster health = {}",
                       player.get_health(),
                       monster.get_health() );

        monster.get_hurt( player.get_attack() );

        if ( !monster.is_dead() )
        {
            player.get_hurt( monster.get_attack() );
        }
    }
}

} // namespace asciinem::server::domain
