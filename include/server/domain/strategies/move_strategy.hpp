#ifndef ASCIINEM_SERVER_MOVE_STRATEGY_H
#define ASCIINEM_SERVER_MOVE_STRATEGY_H

#include "server/domain/entity.hpp"

#include <memory>
#include <utility>

namespace asciinem::server::domain
{

class move_strategy
{
public:
    using pointer = std::shared_ptr<move_strategy>;
    virtual ~move_strategy() = default;

    virtual auto move() -> entity::position_type = 0;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_MOVE_STRATEGY_H
