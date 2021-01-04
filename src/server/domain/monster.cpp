
#include "server/domain/monster.hpp"

#include <utility>

namespace asciinem::server::domain
{

monster::monster( std::string name,
                  asciinem::server::domain::entity::position_type position,
                  int health,
                  int level,
                  move_strategy::pointer strategy )
    : entity( std::move( name ), position, health, level ),
      strategy_( std::move( strategy ) )
{
}

auto monster::get_attack() -> int
{
    return this->get_level();
}

auto monster::get_defense() -> int
{
    const double half = 0.5;
    return static_cast<int>( half * this->get_level() );
}

auto monster::move() -> entity::position_type
{
    return strategy_->move();
}

void monster::set_strategy( const move_strategy::pointer& strategy )
{
    strategy_ = strategy;
}

} // namespace asciinem::server::domain
