#include "server/domain/health_potion.hpp"

#include <utility>

namespace asciinem::server::domain
{

health_potion::health_potion(
    int id, std::string name, double value, int level, int power )
    : item( id, std::move( name ), value, level ), power_( power )
{
}

auto health_potion::get_power() const -> int
{
    return power_;
}

void health_potion::set_power( int power )
{
    power_ = power;
}

} // namespace asciinem::server::domain