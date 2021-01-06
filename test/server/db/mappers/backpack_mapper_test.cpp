#include "server/db/database.hpp"
#include "server/db/mappers/player_mapper.hpp"
#include "server/db/sqlite_connection.hpp"

#include <catch2/catch.hpp>
#include <filesystem>

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

TEST_CASE( "Create table backpacks", "[server][db]" )
{
    const auto db_name = "backpack_test"s;
    const auto db_path = db_name + ".db";
    const auto db = db::database<db::sqlite_connection> { db_name };
    db::item_mapper { db };
    db::player_mapper { db };
    db::backpack_mapper { db };

    const auto* query = "INSERT INTO backpacks (player_login, item_id) "
                        "VALUES (\"test\", 1);";
    auto result = db.run_query( query );

    REQUIRE( !result.has_value() );

    query = "SELECT * FROM backpacks;";
    result = db.run_query( query );

    REQUIRE( result.has_value() );
    REQUIRE( result->size() == 1 );

    cleanup_db_file( db_path );
}

TEST_CASE( "Create and read backpack", "[server][db]" )
{
    const auto db_name = "player_tests"s;
    const auto db_path = db_name + ".db";
    const auto db = db::database<db::sqlite_connection> { db_name };
    auto im = db::item_mapper { db };   // to create the table items
    auto pm = db::player_mapper { db }; // to create the table players
    auto bm = db::backpack_mapper { db };

    auto op = domain::player( "test", { 0, 0 }, 1, 0, 1., {}, 1 );
    pm.insert( op );

    const auto* query =
        "INSERT INTO items (item_id, name, value, level, defense, "
        "attack) VALUES (1, \"test\", 1, 1 , 1, 1);";
    db.run_query( query );

    query = "INSERT INTO backpacks (player_login, item_id) "
            "VALUES (\"test_user\", 1)";
    bm.insert_player_item( "test", im.record_to_item( im.find_by_id( 1 ) ) );
    db.run_query( query );

    auto backpack = bm.get_backpack_for_player( "test_user" );
    REQUIRE_FALSE( backpack.empty() );

    cleanup_db_file( db_path );
}