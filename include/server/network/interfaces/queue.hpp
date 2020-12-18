#ifndef ASCIINEM_QUEUE_HPP
#define ASCIINEM_QUEUE_HPP

#include "server/network/types.hpp"

#include <memory>

namespace asciinem::server::network
{

class queue : public std::enable_shared_from_this<queue>
{
public:
    using pointer = std::shared_ptr<queue>;

    queue() = default;
    queue( const queue& ) = default;
    queue( queue&& ) noexcept = default;
    auto operator=( const queue& ) -> queue& = default;
    auto operator=( queue&& ) noexcept -> queue& = default;

    virtual ~queue() = default;

    virtual auto pop() -> types::msg = 0;
    virtual auto pop_wait() -> types::msg = 0;
    virtual void push( types::msg ) = 0;
    virtual auto back() -> types::msg = 0;
    virtual auto front() -> types::msg = 0;
    virtual auto size() -> std::size_t = 0;
    virtual auto empty() -> bool = 0;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_QUEUE_HPP
