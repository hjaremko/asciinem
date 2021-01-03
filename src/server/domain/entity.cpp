#include "server/domain/entity.hpp"

#include <utility>
namespace asciinem::server::domain
{

entity::entity( std::string name,
                std::pair<int, int> position,
                int health,
                int level )
    : name_( std::move( name ) ), position_( std::move( position ) ),
      health_( health ), level_( level )
{
}

void entity::die()
{
    health_ = 0;
}

auto entity::get_name() const -> const std::string&
{
    return name_;
}

auto entity::get_position() const -> const std::pair<int, int>&
{
    return position_;
}

auto entity::get_health() const -> int
{
    return health_;
}

auto entity::get_level() const -> int
{
    return level_;
}

void entity::set_name( const std::string& name )
{
    name_ = name;
}

void entity::set_position( const std::pair<int, int>& position )
{
    position_ = position;
}

void entity::set_health( int health )
{
    health_ = health;
}

void entity::level_up()
{
    level_++;
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

} // namespace asciinem::server::domain
