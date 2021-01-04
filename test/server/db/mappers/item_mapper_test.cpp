#include "server/db/database.hpp"
#include "server/db/mappers/item_mapper.hpp"
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

TEST_CASE( "Create table items", "[server][db]" )
{
    const auto db_name = "item_tests"s;
    const auto db_path = db_name + ".db";
    const auto db = db::database<db::sqlite_connection> { db_name };
    db::item_mapper { db };

    const auto* query = "INSERT INTO items (name, value, level, defense, "
                        "attack) VALUES (\"test\", 1, 1 , 1, 1);";
    auto result = db.run_query( query );

    REQUIRE( !result.has_value() );

    query = "SELECT * FROM items;";
    result = db.run_query( query );

    REQUIRE( result.has_value() );
    REQUIRE( result->size() == 1 );

    cleanup_db_file( db_path );
}

TEST_CASE( "Update table items", "[server][db]" )
{
    const auto db_name = "item_tests"s;
    const auto db_path = db_name + ".db";
    const auto db = db::database<db::sqlite_connection> { db_name };
    auto im = db::item_mapper { db };

    const auto* query = "INSERT INTO items (name, value, level, defense, "
                        "attack) VALUES (\"test\", 1, 1, 1, 1);";
    db.run_query( query );

    query = "SELECT * FROM items;";
    auto result = db.run_query( query );
    auto record = *result->begin();
    auto i = im.record_to_item( record );

    i->set_name( "updated_test" );
    im.update( *i );

    query = "SELECT * FROM items;";
    result = db.run_query( query );

    REQUIRE( result.has_value() );
    REQUIRE( result->size() == 1 );

    record = *result->begin();
    auto i2 = im.record_to_item( record );

    REQUIRE( *i == *i2 );

    cleanup_db_file( db_path );
}