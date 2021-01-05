#include "server/domain/collision_checker.hpp"

#include <catch2/catch.hpp>
#include <memory>

using namespace asciinem::server::domain;

TEST_CASE( "Check entities collision", "[server][domain]" )
{
    auto position = std::pair<int, int>( 0, 0 );
    auto diff_position = std::pair<int, int>( 1, 1 );

    REQUIRE( collision_checker::check_collision( position, position ) );
    REQUIRE_FALSE(
        collision_checker::check_collision( position, diff_position ) );
}

TEST_CASE( "Check location collision", "[server][domain]" )
{
    std::vector<std::string> map = {
        "+------------------------+", "|                        |",
        "|          ##            |", "|         ####           |",
        "|   ##     ||     ##     |", "|  ####          ####    |",
        "|   ||  ##        ||     |", "|      ####              |",
        "|       ||               |", "|                        |",
        "+------------------------+"
    };

    auto l = location( "../../locations/test_map.txt",
                       "../../locations/test_collisions.txt" );

    auto collision = std::pair<int, int>( 0, 0 );
    auto no_collision = std::pair<int, int>( 1, 1 );

    REQUIRE( collision_checker::check_collision( collision, l ) );
    REQUIRE_FALSE( collision_checker::check_collision( no_collision, l ) );
}