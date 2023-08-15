#include "server/domain/strategies/still_strategy.hpp"

namespace asciinem::server::domain
{

auto still_strategy::move() -> entity::position_type
{
    return std::pair<int, int>(0, 0);
}

} // namespace asciinem::server::domain
