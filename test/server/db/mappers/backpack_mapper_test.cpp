#include "server/db/database.hpp"
#include "server/db/mappers/player_mapper.hpp"
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

TEST_CASE("Create table backpacks", "[server][db]")
{
    const auto db_name = "backpack_test"s;
    const auto db_path = db_name + ".db";
    const auto db = db::database<db::sqlite_connection>{db_name};
    db::item_mapper{db};
    db::player_mapper{db};
    db::backpack_mapper{db};

    const auto* query = "INSERT INTO backpacks (player_login, item_name) "
                        "VALUES (\"test_player\", \"test_item\");";
    auto result = db.run_query(query);

    REQUIRE(!result.has_value());

    query = "SELECT * FROM backpacks;";
    result = db.run_query(query);

    REQUIRE(result.has_value());
    REQUIRE(result->size() == 1);

    cleanup_db_file(db_path);
}

TEST_CASE("Create and read backpack", "[server][db]")
{
    const auto db_name = "backpack_test"s;
    const auto db_path = db_name + ".db";
    const auto db = db::database<db::sqlite_connection>{db_name};
    auto im = db::item_mapper{db};   // to create the table items
    auto pm = db::player_mapper{db}; // to create the table players
    auto bm = db::backpack_mapper{db};

    auto op = domain::player("test_player", {0, 0}, 1, 0, 1., {}, 1);
    pm.insert(op);

    auto oi = domain::armor("test_item", 1, 1, 1);
    im.insert(oi);

    bm.insert_player_item("test_player", "test_item");

    auto backpack = bm.get_backpack_for_player("test_player");
    REQUIRE_FALSE(backpack.empty());

    cleanup_db_file(db_path);
}
