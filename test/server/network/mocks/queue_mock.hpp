#ifndef ASCIINEM_QUEUE_MOCK_HPP
#define ASCIINEM_QUEUE_MOCK_HPP

#include "server/network/interfaces/queue.hpp"
#include "server/network/types.hpp"

#include "gmock/gmock.h"

class queue_mock : public asciinem::server::network::queue
{
public:
    MOCK_METHOD(asciinem::server::network::types::msg, pop, (), ());
    MOCK_METHOD(asciinem::server::network::types::msg, pop_wait, (), ());
    MOCK_METHOD(void, push, (asciinem::server::network::types::msg), ());
    MOCK_METHOD(asciinem::server::network::types::msg, back, (), ());
    MOCK_METHOD(asciinem::server::network::types::msg, front, (), ());
    MOCK_METHOD(std::size_t, size, (), ());
    MOCK_METHOD(bool, empty, (), ());
};

#endif // ASCIINEM_QUEUE_MOCK_HPP
