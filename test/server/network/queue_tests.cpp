#include "server/network/message_queue.hpp"

#include <catch2/catch.hpp>
#include <future>
#include <spdlog/spdlog.h>
#include <thread>

using namespace std::chrono_literals;
using namespace asciinem::server::network;

namespace
{

template <int Amount>
auto make_pushers(queue& q)
{
    auto poosher = [&q]()
    {
        std::this_thread::sleep_for(300ms);
        q.push(std::to_string(1));
    };
    auto pushers = std::vector<std::future<void>>{};

    for (int i = 0; i < Amount; ++i)
    {
        pushers.push_back(std::async(std::launch::async, poosher));
    }

    return pushers;
}

template <int Amount>
auto make_popper(queue& q, int& sum)
{
    auto popper = [&]()
    {
        auto elems = 0;

        while (elems < Amount)
        {
            spdlog::debug("Current elems: {}", elems);
            auto popped = std::stoi(q.pop_wait());
            sum += popped;
            ++elems;
        }
    };

    return std::async(std::launch::async, popper);
}

} // namespace

TEST_CASE("Queue thread safety test", "[network], [queue]")
{
    spdlog::default_logger_raw()->set_level(spdlog::level::debug);

    auto q = message_queue{};
    auto expected_sum = 0;

    constexpr auto thread_amount = 100;

    {
        auto pushers = make_pushers<thread_amount>(q);
        auto popper = make_popper<thread_amount>(q, expected_sum);
    }

    REQUIRE(q.size() == 0);
    REQUIRE(expected_sum == 100);
}

TEST_CASE("Queue size test", "[network], [queue]")
{
    spdlog::default_logger_raw()->set_level(spdlog::level::debug);

    auto q = message_queue{};

    REQUIRE(q.size() == 0);
    REQUIRE(q.empty());

    q.push("1");
    q.push("2");
    q.push("3");

    REQUIRE(q.size() == 3);
    REQUIRE(!q.empty());

    q.pop();
    q.pop();
    q.pop();

    REQUIRE(q.size() == 0);
    REQUIRE(q.empty());
}

TEST_CASE("Popping empty queue should throw exception", "[network], [queue]")
{
    auto q = message_queue{};

    REQUIRE_THROWS(q.pop());
}

TEST_CASE("Front on empty queue should throw exception", "[network], [queue]")
{
    auto q = message_queue{};

    REQUIRE_THROWS(q.front());
}

TEST_CASE("Back on empty queue should throw exception", "[network], [queue]")
{
    auto q = message_queue{};

    REQUIRE_THROWS(q.back());
}
