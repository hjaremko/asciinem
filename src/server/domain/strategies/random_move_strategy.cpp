#include "server/domain/strategies/random_move_strategy.hpp"

#include "server/domain/entity.hpp"

#include <cstdlib>
#include <random>

namespace asciinem::server::domain
{

auto random_move_strategy::move() -> entity::position_type
{
    const double half = 0.5;

    auto dev = std::random_device {};
    auto rng = std::mt19937 { dev() };
    auto dist = std::uniform_real_distribution<>{ 0., 1. };
    auto x = dist( rng ) > half ? 1 : 0;
    auto y = dist( rng ) > half ? 1 : 0;
    return std::pair<int, int>( x, y );
}

} // namespace asciinem::server::domain