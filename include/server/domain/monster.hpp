#ifndef ASCIINEM_SERVER_MONSTER_H
#define ASCIINEM_SERVER_MONSTER_H

#include "entity.hpp"
#include "strategies/move_strategy.hpp"
#include "strategies/random_move_strategy.hpp"

namespace asciinem::server::domain
{

class monster : public entity
{
public:
    monster( std::string name,
             position_type position,
             int health,
             int level,
             move_strategy::pointer strategy =
                 std::make_shared<random_move_strategy>() );

    auto get_attack() -> int override;
    auto get_defense() -> int override;

    void set_strategy( const move_strategy::pointer& strategy );

    auto move() -> entity::position_type;

private:
    move_strategy::pointer strategy_;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_MONSTER_H
