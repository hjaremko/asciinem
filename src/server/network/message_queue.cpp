#include "network/message_queue.hpp"

#include <spdlog/spdlog.h>

namespace asciinem::server::network
{

auto message_queue::pop() -> types::msg
{
    auto lock = std::lock_guard<std::mutex> { mutex_ };
    throw_if_empty();

    auto popped = queue_.front();
    queue_.pop_front();

    spdlog::debug( "Popped element: {}", popped );

    return popped;
}

auto message_queue::pop_wait() -> types::msg
{
    spdlog::debug( "Waiting on a element in the queue..." );

    while ( empty() )
    {
    }

    return pop();
}

void message_queue::push( types::msg msg )
{
    auto lock = std::lock_guard<std::mutex> { mutex_ };

    spdlog::debug( "Pushed element: {}", msg );

    queue_.emplace_back( std::move( msg ) );
}

auto message_queue::back() -> types::msg
{
    auto lock = std::lock_guard<std::mutex> { mutex_ };
    throw_if_empty();

    return queue_.back();
}

auto message_queue::front() -> types::msg
{
    auto lock = std::lock_guard<std::mutex> { mutex_ };
    throw_if_empty();

    return queue_.front();
}

auto message_queue::size() -> std::size_t
{
    auto lock = std::lock_guard<std::mutex> { mutex_ };

    return queue_.size();
}

auto message_queue::empty() -> bool
{
    auto lock = std::lock_guard<std::mutex> { mutex_ };

    return queue_.empty();
}

void message_queue::throw_if_empty() const
{
    if ( queue_.empty() )
    {
        throw std::runtime_error { "Message queue is empty" };
    }
}

} // namespace asciinem::server::network
