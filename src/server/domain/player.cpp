#include "server/domain/player.hpp"

#include <algorithm>
#include <set>
#include <utility>

namespace asciinem::server::domain
{

player::player( const std::string& name )
    : entity( name, "\\o>", { 28, 26 }, 1 ), exp_( 0 ), money_( 10. ), // NOLINT
      backpack_( {} ), backpack_capacity_( 5 )                         // NOLINT
{
}

player::player( const std::string& name,
                const entity::position_type& position,
                int level,
                int exp,
                double amount,
                std::set<item::pointer> backpack,
                unsigned int backpack_capacity,
                weapon::pointer weapon,
                armor::pointer armor )
    : entity( name, "\\o>", position, level ), exp_( exp ),
      money_( money( amount ) ), backpack_( std::move( backpack ) ),
      backpack_capacity_( std::min(
          backpack_capacity, static_cast<unsigned int>( 10 ) ) ), // NOLINT
      weapon_( std::move( weapon ) ), armor_( std::move( armor ) )
{
}

player::player( const std::string& name,
                const entity::position_type& position,
                int health,
                int level,
                int exp,
                double amount,
                std::set<item::pointer> backpack,
                unsigned int backpack_capacity,
                weapon::pointer weapon,
                armor::pointer armor )
    : entity( name, "\\o>", position, health, level ), exp_( exp ),
      money_( money( amount ) ), backpack_( std::move( backpack ) ),
      backpack_capacity_( std::min(
          backpack_capacity, static_cast<unsigned int>( 10 ) ) ), // NOLINT
      weapon_( std::move( weapon ) ), armor_( std::move( armor ) )
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
                         [ item ]( const auto& x )
                         { return *x == item; } ) != backpack_.end();
}

auto player::get_attack() const -> int
{
    return 2 * this->get_level() + ( weapon_ ? weapon_->get_attack() : 0 );
}

auto player::get_defense() const -> int
{
    return this->get_level() + ( armor_ ? armor_->get_defense() : 0 );
}

auto player::get_backpack_capacity() const -> unsigned int
{
    return backpack_capacity_;
}

void player::set_backpack_capacity( unsigned int backpackCapacity )
{
    backpack_capacity_ =
        std::min( backpackCapacity, static_cast<unsigned int>( 10 ) ); // NOLINT
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

auto player::get_exp() const -> int
{
    return exp_;
}

auto player::gain_exp( int exp ) -> bool
{
    exp_ += exp;
    if ( exp_ > 100 * level_ ) // NOLINT
    {
        level_up();
        return true;
    }
    return false;
}

void player::set_money( double amount )
{
    money_ = money( amount );
}

void player::level_up()
{
    entity::level_up();
    if ( level_ % 4 )
    {
        backpack_capacity_++;
    }
    money_ += money( 100. );
    exp_ = 0;
}

void player::reset()
{
    *this = player( name_ );
}

void player::gain_health( int health )
{
    health_ = std::min( health_ + health, get_max_health() );
}

void player::set_weapon( const weapon::pointer& weapon )
{
    weapon_ = weapon;
}

void player::set_armor( const armor::pointer& armor )
{
    armor_ = armor;
}

} // namespace asciinem::server::domain