#include "server/domain/monster.hpp"

#include <catch2/catch.hpp>
#include <memory>
#include <server/domain/strategies/still_strategy.hpp>

using namespace asciinem::server::domain;

TEST_CASE( "Create monster", "[server][domain]" )
{
    const int level = 10;
    const double half = 0.5;
    auto m = std::make_unique<monster>( "test_monster",
                                        std::pair<int, int>( 0, 0 ),
                                        1,
                                        level,
                                        std::make_shared<still_strategy>() );

    REQUIRE( m->get_attack() == level );
    REQUIRE( m->get_defense() == half * level );
    REQUIRE( m->move() == std::pair<int, int>( 0, 0 ) );
}