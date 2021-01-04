#include "server/domain/weapon.hpp"

#include <utility>
namespace asciinem::server::domain
{

weapon::weapon( int id, std::string name, double value, int level, int attack )
    : item( id, std::move( name ), value, level ), attack_( attack )
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
