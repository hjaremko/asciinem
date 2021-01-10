
#include "server/domain/monster.hpp"

#include <utility>

namespace asciinem::server::domain
{

monster::monster( std::string name,
                  asciinem::server::domain::entity::position_type position,
                  int level,
                  move_strategy::pointer strategy )
    : entity( std::move( name ), "@", position, level ),
      strategy_( std::move( strategy ) )
{
}

monster::monster( std::string name,
                  asciinem::server::domain::entity::position_type position,
                  int health,
                  int level,
                  move_strategy::pointer strategy )
    : entity( std::move( name ), "@", position, health, level ),
      strategy_( std::move( strategy ) )
{
}

auto monster::get_attack() const -> int
{
    return this->get_level();
}

auto monster::get_defense() const -> int
{
    return static_cast<int>( 0.5 * this->get_level() ); // NOLINT
}

auto monster::move() -> entity::position_type
{
    return strategy_->move();
}

void monster::set_strategy( const move_strategy::pointer& strategy )
{
    strategy_ = strategy;
}

auto monster::get_id() const -> int
{
    return id_;
}

} // namespace asciinem::server::domain
