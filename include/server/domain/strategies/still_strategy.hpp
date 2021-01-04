#ifndef ASCIINEM_SERVER_STILL_STRATEGY_H
#define ASCIINEM_SERVER_STILL_STRATEGY_H

#include "move_strategy.hpp"
#include "server/domain/entity.hpp"

namespace asciinem::server::domain
{

class still_strategy : public move_strategy
{
public:
    auto move() -> entity::position_type override;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_STILL_STRATEGY_H
