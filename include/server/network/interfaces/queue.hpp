#ifndef ASCIINEM_QUEUE_HPP
#define ASCIINEM_QUEUE_HPP

#include "network/types.hpp"

namespace asciinem::server::network
{

class queue
{
public:
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
