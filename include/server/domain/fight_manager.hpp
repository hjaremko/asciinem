#ifndef ASCIINEM_SERVER_FIGHT_MANAGER_H
#define ASCIINEM_SERVER_FIGHT_MANAGER_H

#include "monster.hpp"
#include "player.hpp"

namespace asciinem::server::domain
{

class fight_manager
{
public:
    static void fight(player& player, monster& monster)
    {
        while (!player.is_dead() && !monster.is_dead())
        {
            spdlog::trace(
                "Player health = {}, monster health = {}",
                player.get_health(),
                monster.get_health()
            );

            monster.get_hurt(player.get_attack());

            if (!monster.is_dead())
            {
                player.get_hurt(monster.get_attack());
            }
        }
    }
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_FIGHT_MANAGER_H
