#include "server/domain/armor.hpp"

#include "server/domain/player.hpp"

#include <utility>
namespace asciinem::server::domain
{

armor::armor( std::string name, double value, int level, int defense )
    : item( std::move( name ), value, level ), defense_( defense )
{
}

auto armor::get_defense() const -> int
{
    return defense_;
}

void armor::set_defense( int defense )
{
    defense_ = defense;
}

void armor::use( player& p )
{
    if ( get_level() <= p.get_level() )
    {
        if ( p.has( *this ) )
        {
            p.take_from_backpack( shared_from_this() );
            if ( p.get_armor() )
            {
                p.add_to_backpack( shared_from_this() );
            }
        }
        p.set_armor( shared_from_this() );
    }
}

} // namespace asciinem::server::domain
