#include "server/domain/item.hpp"

#include <tuple>
#include <utility>
namespace asciinem::server::domain
{

item::item( std::string name, double value, int level )
    : name_( std::move( name ) ), value_( money( value ) ), level_( level )
{
}

auto item::get_name() const -> std::string
{
    return name_;
}

auto item::get_value() const -> money
{
    return value_;
}

auto item::get_level() const -> int
{
    return level_;
}

void item::set_value( double value )
{
    value_ = money( value );
}

void item::set_name( const std::string& name )
{
    name_ = name;
}

auto operator<( const item& lhs, const item& rhs ) -> bool
{
    return std::tie( lhs.name_, lhs.value_, lhs.level_ ) <
           std::tie( rhs.name_, rhs.value_, rhs.level_ );
}

auto operator==( const item& lhs, const item& rhs ) -> bool
{
    return std::tie( lhs.name_, lhs.value_, lhs.level_ ) ==
           std::tie( rhs.name_, rhs.value_, rhs.level_ );
}

auto operator!=( const item& lhs, const item& rhs ) -> bool
{
    return !( rhs == lhs );
}

void item::use( player& /*unused*/ )
{
}

} // namespace asciinem::server::domain
