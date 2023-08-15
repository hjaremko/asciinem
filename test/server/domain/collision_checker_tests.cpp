#include "server/domain/collision_checker.hpp"

#include <catch2/catch.hpp>
#include <memory>

using namespace asciinem::server::domain;

TEST_CASE("Check entities collision", "[server][domain]")
{
    auto position = std::pair<int, int>(0, 0);
    auto diff_position = std::pair<int, int>(1, 0);

    REQUIRE(collision_checker::check_collision(position, 3, position, 1));
    REQUIRE(collision_checker::check_collision(position, 3, diff_position, 1));
    REQUIRE_FALSE(
        collision_checker::check_collision(position, 1, diff_position, 1)
    );
}

TEST_CASE("Check location collision", "[server][domain]")
{
    std::vector<std::string> map = {
        "+------------------------+",
        "|                        |",
        "|          ##            |",
        "|         ####           |",
        "|   ##     ||     ##     |",
        "|  ####          ####    |",
        "|   ||  ##        ||     |",
        "|      ####              |",
        "|       ||               |",
        "|                        |",
        "+------------------------+"};

    auto l = location(
        "../../locations/test_map.txt",
        "../../locations/test_collisions.txt"
    );

    auto collision = std::pair<int, int>(0, 0);
    auto no_collision = std::pair<int, int>(3, 4);

    REQUIRE(collision_checker::check_collision(collision, 1, l));
    REQUIRE(collision_checker::check_collision(no_collision, 3, l));
    REQUIRE_FALSE(collision_checker::check_collision(no_collision, 1, l));
}
