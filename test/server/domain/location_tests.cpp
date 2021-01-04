#include "server/domain/location.hpp"

#include <catch2/catch.hpp>
#include <memory>

using namespace asciinem::server::domain;

TEST_CASE( "Read location data", "[server][domain]" )
{
    std::vector<std::string> map = {
        "+------------------------+", "|                        |",
        "|          ##            |", "|         ####           |",
        "|   ##     ||     ##     |", "|  ####          ####    |",
        "|   ||  ##        ||     |", "|      ####              |",
        "|       ||               |", "|                        |",
        "+------------------------+"
    };

    auto l = std::make_shared<location>(
        "../../locations/test_map.txt", "../../locations/test_collisions.txt" );

    REQUIRE( l->get_map() == map );
    REQUIRE( l->get_collision_map()[ 0 ][ 0 ] );
    REQUIRE_FALSE( l->get_collision_map()[ 1 ][ 1 ] );
}