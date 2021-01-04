#ifndef ASCIINEM_SERVER_RANDOM_MOVE_STRATEGY_HPP
#define ASCIINEM_SERVER_RANDOM_MOVE_STRATEGY_HPP

#include "move_strategy.hpp"
#include "server/domain/entity.hpp"

#include <utility>

namespace asciinem::server::domain
{

class random_move_strategy : public move_strategy
{
public:
    auto move() -> entity::position_type override;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_RANDOM_MOVE_STRATEGY_HPP
