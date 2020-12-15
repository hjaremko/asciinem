#ifndef ASCIINEM_MESSAGE_QUEUE_HPP
#define ASCIINEM_MESSAGE_QUEUE_HPP

#include "interfaces/queue.hpp"

#include <deque>
#include <memory>
#include <mutex>

namespace asciinem::server::network
{

class message_queue : public queue
{
public:
    message_queue() = default;
    message_queue( const message_queue& ) = delete;
    message_queue( message_queue&& ) noexcept = delete;
    auto operator=( const message_queue& ) -> message_queue& = delete;
    auto operator=( message_queue&& ) noexcept -> message_queue& = delete;
    ~message_queue() override = default;

    auto pop() -> types::msg override;
    auto pop_wait() -> types::msg override;
    void push( types::msg msg ) override;
    auto back() -> types::msg override;
    auto front() -> types::msg override;
    auto size() -> std::size_t override;
    auto empty() -> bool override;

private:
    void throw_if_empty() const;

    std::deque<types::msg> queue_;
    std::mutex mutex_;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_MESSAGE_QUEUE_HPP
