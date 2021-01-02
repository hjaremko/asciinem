#include "server/domain/armor.hpp"

#include <utility>
namespace asciinem::server::domain
{

armor::armor( std::string name, int value, int level, int defense )
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

} // namespace asciinem::server::domain
