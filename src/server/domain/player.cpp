#include "server/domain/player.hpp"

#include <algorithm>
#include <set>
#include <utility>

namespace asciinem::server::domain
{

player::player( const std::string& name,
                const std::pair<int, int>& position,
                int health,
                std::set<item::pointer> backpack,
                unsigned int backpack_capacity )
    : entity( name, position, health, 1 ), backpack_( std::move( backpack ) ),
      backpack_capacity_( backpack_capacity )
{
}

void player::add_to_backpack( const item::pointer& item )
{
    if ( backpack_.size() < backpack_capacity_ )
    {
        backpack_.insert( item );
    }
}

void player::take_from_backpack( const item::pointer& item )
{
    backpack_.erase( item );
}

auto player::has( const item& item ) -> bool
{
    return std::find_if( backpack_.begin(),
                         backpack_.end(),
                         [ item ]( const auto& x ) { return *x == item; } ) !=
           backpack_.end();
}

void player::use( const weapon::pointer& weapon )
{
    if ( weapon->get_level() <= this->get_level() )
    {
        if ( this->has( *weapon ) )
        {
            this->take_from_backpack( weapon );
            if ( weapon_.has_value() )
            {
                this->add_to_backpack( weapon_.value() );
            }
        }
        weapon_ = weapon;
    }
}

void player::use( const armor::pointer& armor )
{
    if ( armor->get_level() <= this->get_level() )
    {
        if ( this->has( *armor ) )
        {
            this->take_from_backpack( armor );
            if ( armor_.has_value() )
            {
                this->add_to_backpack( armor_.value() );
            }
        }
        armor_ = armor;
    }
}

auto player::get_attack() -> int
{
    return this->get_level() +
           ( weapon_.has_value() ? weapon_.value()->get_attack() : 0 );
}

auto player::get_defense() -> int
{
    return this->get_level() +
           ( armor_.has_value() ? armor_.value()->get_defense() : 0 );
}

} // namespace asciinem::server::domain
