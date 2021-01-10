#ifndef ASCIINEM_SERVER_FIGHT_MANAGER_H
#define ASCIINEM_SERVER_FIGHT_MANAGER_H

namespace asciinem::server::domain
{

class player;
class monster;

class fight_manager
{
public:
    static void fight( player& player, monster& monster );
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_FIGHT_MANAGER_H
