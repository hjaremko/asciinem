#include "server/domain/strategies/random_move_strategy.hpp"

#include <random>

namespace asciinem::server::domain
{

auto random_move_strategy::move() -> entity::position_type
{
    static auto dev = std::random_device{};
    static auto rng = std::mt19937{dev()};
    static auto dist = std::uniform_int_distribution<>{-1, 1};

    return std::pair<int, int>(dist(rng), dist(rng));
}

} // namespace asciinem::server::domain
