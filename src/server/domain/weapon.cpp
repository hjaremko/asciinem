#include "server/domain/weapon.hpp"

#include "server/domain/player.hpp"

#include <utility>
namespace asciinem::server::domain
{

weapon::weapon( std::string name, double value, int level, int attack )
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

void weapon::use( player& p )
{
    if ( get_level() <= p.get_level() )
    {
        if ( p.has( *this ) )
        {
            p.take_from_backpack( shared_from_this() );
            if ( p.get_weapon() )
            {
                p.add_to_backpack( shared_from_this() );
            }
        }
        p.set_weapon( shared_from_this() );
    }
}

} // namespace asciinem::server::domain
