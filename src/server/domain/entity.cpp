#include "server/domain/entity.hpp"

#include <utility>
namespace asciinem::server::domain
{

entity::entity( std::string name,
                std::string shape,
                std::pair<int, int> position,
                int health,
                int level )
    : name_( std::move( name ) ), shape_( std::move( shape ) ),
      position_( std::move( position ) ), health_( health ),
      level_( level ) // NOLINT
{
}

entity::entity( std::string name,
                std::string shape,
                std::pair<int, int> position,
                int level )
    : name_( std::move( name ) ), shape_( std::move( shape ) ),
      position_( std::move( position ) ), health_( 100 * level ), // NOLINT
      level_( level )                                             // NOLINT
{
}

auto entity::get_name() const -> std::string
{
    return name_;
}

auto entity::get_position() const -> position_type
{
    return position_;
}

auto entity::get_health() const -> int
{
    return health_;
}

auto entity::get_max_health() const -> int
{
    return 100 * level_; // NOLINT
}

auto entity::get_level() const -> int
{
    return level_;
}

void entity::set_name( const std::string& name )
{
    name_ = name;
}

void entity::set_position( const position_type& position )
{
    position_ = position;
}

void entity::set_health( int health )
{
    health_ = health;
}

auto entity::operator==( const entity& rhs ) const -> bool
{
    return name_ == rhs.name_ && position_ == rhs.position_ &&
           health_ == rhs.health_ && level_ == rhs.level_;
}

auto entity::operator!=( const entity& rhs ) const -> bool
{
    return !( rhs == *this );
}

auto entity::is_dead() const -> bool
{
    return health_ == 0;
}

void entity::level_up()
{
    level_++;
    health_ = std::min( health_ + 25, get_max_health() ); // NOLINT
}

void entity::get_hurt( int damage )
{
    damage = std::max( damage - get_defense(), 0 );
    health_ = std::max( health_ - damage, 0 );
}

auto entity::get_shape() const -> const std::string&
{
    return shape_;
}

void entity::set_shape( const std::string& shape )
{
    shape_ = shape;
}

} // namespace asciinem::server::domain