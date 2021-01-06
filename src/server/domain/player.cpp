#include "server/domain/player.hpp"

#include <algorithm>
#include <set>
#include <utility>

namespace asciinem::server::domain
{

player::player( const std::string& name )
    : entity( name, { 28, 26 }, 1 ), money_( 10. ), // NOLINT
      backpack_( {} ), backpack_capacity_( 10 )     // NOLINT
{
}

player::player( const std::string& name,
                const entity::position_type& position,
                int level,
                double amount,
                std::set<item::pointer> backpack,
                unsigned int backpack_capacity,
                weapon::pointer weapon,
                armor::pointer armor )
    : entity( name, position, level ), money_( money( amount ) ),
      backpack_( std::move( backpack ) ),
      backpack_capacity_( backpack_capacity ), weapon_( std::move( weapon ) ),
      armor_( std::move( armor ) )
{
}

player::player( const std::string& name,
                const entity::position_type& position,
                int health,
                int level,
                double amount,
                std::set<item::pointer> backpack,
                unsigned int backpack_capacity,
                weapon::pointer weapon,
                armor::pointer armor )
    : entity( name, position, health, level ), money_( money( amount ) ),
      backpack_( std::move( backpack ) ),
      backpack_capacity_( backpack_capacity ), weapon_( std::move( weapon ) ),
      armor_( std::move( armor ) )
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
            if ( weapon_ )
            {
                this->add_to_backpack( weapon_ );
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
            if ( armor_ )
            {
                this->add_to_backpack( armor_ );
            }
        }
        armor_ = armor;
    }
}

void player::use( const health_potion::pointer& potion )
{
    if ( potion->get_level() <= this->get_level() )
    {
        health_ = std::min( health_ + potion->get_power(), get_max_health() );
    }
}

auto player::get_attack() const -> int
{
    return this->get_level() + ( weapon_ ? weapon_->get_attack() : 0 );
}

auto player::get_defense() const -> int
{
    return static_cast<int>( 0.5 * this->get_level() + // NOLINT
                             ( armor_ ? armor_->get_defense() : 0 ) );
}

auto player::get_backpack_capacity() const -> unsigned int
{
    return backpack_capacity_;
}

void player::set_backpack_capacity( unsigned int backpackCapacity )
{
    backpack_capacity_ = backpackCapacity;
}

auto player::get_weapon() const -> weapon::pointer
{
    return weapon_;
}

auto player::get_armor() const -> armor::pointer
{
    return armor_;
}

auto player::get_backpack() const -> std::set<item::pointer>
{
    return backpack_;
}

auto player::operator==( const player& rhs ) const -> bool
{
    return static_cast<const entity&>( *this ) ==
               static_cast<const entity&>( rhs ) &&
           money_ == rhs.money_ && backpack_ == rhs.backpack_ &&
           backpack_capacity_ == rhs.backpack_capacity_ &&
           weapon_ == rhs.weapon_ && armor_ == rhs.armor_;
}

auto player::operator!=( const player& rhs ) const -> bool
{
    return !( rhs == *this );
}

auto player::get_money() const -> money
{
    return money_;
}

void player::set_money( double amount )
{
    money_ = money( amount );
}

void player::level_up()
{
    entity::level_up();
    backpack_capacity_++;
    money_ += money( 100. );
}

void player::get_hurt( int damage )
{
    entity::get_hurt( damage );
    if ( is_dead() )
    {
        *this = player( name_ );
    }
}

} // namespace asciinem::server::domain
