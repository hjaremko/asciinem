#include "server/db/database.hpp"
#include "server/db/mappers/item_mapper.hpp"
#include "server/db/sqlite_connection.hpp"

#include <catch2/catch.hpp>
#include <filesystem>

using namespace asciinem::server;
using namespace std::string_literals;

namespace
{

void cleanup_db_file(const std::string& path)
{
    if (std::filesystem::exists(path))
    {
        std::filesystem::remove(path);
    }
}

} // namespace

TEST_CASE("Create table items", "[server][db]")
{
    const auto db_name = "item_tests"s;
    const auto db_path = db_name + ".db";
    const auto db = db::database<db::sqlite_connection>{db_name};
    db::item_mapper{db};

    const auto* query = "INSERT INTO items (name, value, level) VALUES "
                        "(\"test\", 1, 1);";
    auto result = db.run_query(query);

    REQUIRE(!result.has_value());

    query = "SELECT * FROM items;";
    result = db.run_query(query);

    REQUIRE(result.has_value());
    REQUIRE_FALSE(result->empty());

    cleanup_db_file(db_path);
}

TEST_CASE("Update table items", "[server][db]")
{
    const auto db_name = "item_tests"s;
    const auto db_path = db_name + ".db";
    const auto db = db::database<db::sqlite_connection>{db_name};
    auto im = db::item_mapper{db};

    auto oi = domain::armor("test_item", 1, 1, 1);
    im.insert(oi);

    auto record = im.find_by_name("test_item");
    auto i = im.record_to_armor(record);

    i->set_value(10.50); // NOLINT
    im.update(*i);

    record = im.find_by_name("test_item");
    auto i2 = im.record_to_armor(record);

    REQUIRE(*i == *i2);

    cleanup_db_file(db_path);
}
