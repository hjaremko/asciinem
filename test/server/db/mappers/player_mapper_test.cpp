#include "server/db/database.hpp"
#include "server/db/mappers/player_mapper.hpp"
#include "server/db/sqlite_connection.hpp"

#include <catch2/catch.hpp>
#include <filesystem>
#include <server/db/mappers/item_mapper.hpp>

using namespace asciinem::server;
using namespace std::string_literals;

namespace
{

void cleanup_db_file( const std::string& path )
{
    if ( std::filesystem::exists( path ) )
    {
        std::filesystem::remove( path );
    }
}

} // namespace

TEST_CASE( "Create table players", "[db]" )
{
    const auto db_name = "player_tests"s;
    const auto db_path = db_name + ".db";
    const auto db = db::database<db::sqlite_connection> { db_name };
    db::item_mapper { db };
    db::player_mapper { db };

    const auto* query =
        "INSERT INTO players (login, pos_x, pos_y, health, level, "
        "backpack_capacity) VALUES (\"test\", 0, 0 , 1, 1, 1);";
    auto result = db.run_query( query );

    REQUIRE( !result.has_value() );

    query = "SELECT * FROM players;";
    result = db.run_query( query );

    REQUIRE( result.has_value() );
    REQUIRE( result->size() == 1 );

    cleanup_db_file( db_path );
}

TEST_CASE( "Update table players", "[db]" )
{
    const auto db_name = "player_tests"s;
    const auto db_path = db_name + ".db";
    const auto db = db::database<db::sqlite_connection> { db_name };
    db::item_mapper { db }; // to create the table items
    auto pm = db::player_mapper { db };

    const auto* query =
        "INSERT INTO players (login, pos_x, pos_y, health, level, "
        "backpack_capacity) VALUES (\"test\", 0, 0 , 1, 1, 1);";
    db.run_query( query );

    query = "SELECT * FROM players;";
    auto result = db.run_query( query );
    auto record = *result->begin();
    auto p = pm.record_to_player( record );

    p->level_up();
    pm.update( *p );

    query = "SELECT * FROM players;";
    result = db.run_query( query );

    REQUIRE( result.has_value() );
    REQUIRE( result->size() == 1 );

    record = *result->begin();
    auto p2 = pm.record_to_player( record );

    REQUIRE( *p == *p2 );

    cleanup_db_file( db_path );
}