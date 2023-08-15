#include "server/domain/health_potion.hpp"

#include "server/domain/player.hpp"

#include <utility>

namespace asciinem::server::domain
{

health_potion::health_potion(
    std::string name,
    double value,
    int level,
    int power
)
    : item(std::move(name), value, level)
    , power_(power)
{
}

auto health_potion::get_power() const -> int
{
    return power_;
}

void health_potion::set_power(int power)
{
    power_ = power;
}

void health_potion::use(player& p)
{
    if (get_level() <= p.get_level())
    {
        if (p.has(*this))
        {
            p.gain_health(get_power());
            p.take_from_backpack(shared_from_this());
        }
    }
}

} // namespace asciinem::server::domain
