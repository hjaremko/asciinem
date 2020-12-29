#include "server/domain/weapon.hpp"

#include <utility>
namespace asciinem::server::domain
{

weapon::weapon( std::string name, int value, int level, int attack )
    : item( std::move( name ), value, level ), attack_( attack )
{
}

auto weapon::get_attack() const -> int
{
    return attack_;
}

void weapon::set_attack( int attack )
{
    attack_ = attack;
}

} // namespace asciinem::server::domain
