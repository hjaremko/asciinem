#include "server/domain/player.hpp"

#include <catch2/catch.hpp>
#include <memory>

using namespace asciinem::server::domain;

TEST_CASE( "Basic use of the backpack", "[server][domain]" )
{
    auto i = std::make_shared<weapon>( "test", 1, 1, 1 );
    auto p = player( "name", { 1, 1 }, 1, 0, 1, {}, 1 );

    REQUIRE_FALSE( p.has( *i ) );
    p.add_to_backpack( i );
    REQUIRE( p.has( *i ) );
    p.take_from_backpack( i );
    REQUIRE_FALSE( p.has( *i ) );
}

TEST_CASE( "Backpack capacity", "[server][domain]" )
{
    auto i_1 = std::make_shared<armor>( "test1", 1, 1, 1 );
    auto i_2 = std::make_shared<weapon>( "test2", 1, 1, 1 );
    auto p = player( "name", { 1, 1 }, 1, 0, 1, {}, 1 );

    p.add_to_backpack( i_1 );
    REQUIRE( p.has( *i_1 ) );
    p.add_to_backpack( i_2 );
    REQUIRE_FALSE( p.has( *i_2 ) );
}

TEST_CASE( "Player's armor", "[server][domain]" ) // NOLINT
{
    auto i_1 = std::make_shared<armor>( "test1", 1, 1, 1 );
    auto i_2 = std::make_shared<armor>( "test2", 1, 1, 2 );
    auto i_3 = std::make_shared<armor>( "test3", 1, 2, 3 );
    auto p = player( "name", { 1, 1 }, 1, 1, 1, {}, 2 );

    p.add_to_backpack( i_1 );
    REQUIRE( p.has( *i_1 ) );
    REQUIRE( p.get_attack() == 2 * p.get_level() );
    REQUIRE( p.get_defense() == p.get_level() );

    i_1->use( p );
    REQUIRE_FALSE( p.has( *i_1 ) );
    REQUIRE( p.get_attack() == 2 * p.get_level() );
    REQUIRE( p.get_defense() == p.get_level() + i_1->get_defense() );

    i_2->use( p );
    REQUIRE_FALSE( p.has( *i_2 ) );
    REQUIRE( p.get_attack() == 2 * p.get_level() );
    REQUIRE( p.get_defense() == p.get_level() + i_2->get_defense() );

    // the armor doesn't change because i_3 has higher level than the players'
    i_3->use( p );
    REQUIRE_FALSE( p.has( *i_3 ) );
    REQUIRE( p.get_attack() == 2 * p.get_level() );
    REQUIRE( p.get_defense() == p.get_level() + i_2->get_defense() );
}

TEST_CASE( "Player's weapon", "[domain]" ) // NOLINT
{
    auto i_1 = std::make_shared<weapon>( "test1", 1, 1, 1 );
    auto i_2 = std::make_shared<weapon>( "test2", 1, 1, 2 );
    auto i_3 = std::make_shared<weapon>( "test3", 1, 2, 3 );
    auto p = player( "name", { 1, 1 }, 1, 1, 1, {}, 2 );

    p.add_to_backpack( i_1 );
    REQUIRE( p.has( *i_1 ) );
    REQUIRE( p.get_defense() == p.get_level() );
    REQUIRE( p.get_attack() == 2 * p.get_level() );

    i_1->use( p );
    REQUIRE_FALSE( p.has( *i_1 ) );
    REQUIRE( p.get_defense() == p.get_level() );
    REQUIRE( p.get_attack() == 2 * p.get_level() + i_1->get_attack() );

    i_2->use( p );
    REQUIRE_FALSE( p.has( *i_2 ) );
    REQUIRE( p.get_defense() == p.get_level() );
    REQUIRE( p.get_attack() == 2 * p.get_level() + i_2->get_attack() );

    // the weapon doesn't change because i_3 has higher level than the players'
    i_3->use( p );
    REQUIRE_FALSE( p.has( *i_2 ) );
    REQUIRE( p.get_defense() == p.get_level() );
    REQUIRE( p.get_attack() == 2 * p.get_level() + i_2->get_attack() );
}

TEST_CASE( "Player getting hurt", "[server][domain]" )
{
    auto p = player( "name", { 1, 1 }, 1, 0, 1, {}, 0 ); // NOLINT
    p.get_hurt( 10 );                                    // NOLINT

    REQUIRE_FALSE( p.is_dead() );
    REQUIRE( p.get_health() == 91 );

    p.get_hurt( 100 ); // NOLINT
    REQUIRE( p.is_dead() );
}