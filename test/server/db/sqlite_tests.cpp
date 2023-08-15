#include "server/db/database.hpp"
#include "server/db/sqlite_connection.hpp"

#include <catch2/catch.hpp>
#include <filesystem>

using namespace asciinem::server;
using namespace std::chrono_literals;
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

TEST_CASE("Db should be initialized successfully if does not exist", "[db]")
{
    spdlog::default_logger_raw()->set_level(spdlog::level::debug);

    const auto db_name = "init_test"s;
    const auto db_path = db_name + ".db";
    const auto db = db::database<db::sqlite_connection>{db_name};

    REQUIRE(std::filesystem::exists(db_path));
    std::filesystem::remove(db_path);
    REQUIRE(!std::filesystem::exists(db_path));
}

TEST_CASE("Create table query should be executed successfully", "[db]")
{
    spdlog::default_logger_raw()->set_level(spdlog::level::debug);

    const auto db_name = "create_db_test"s;
    const auto db_path = db_name + ".db";
    cleanup_db_file(db_path);

    const auto db = db::database<db::sqlite_connection>{db_name};

    REQUIRE(std::filesystem::exists(db_path));

    const auto* books_create =
        "create table books (id integer primary key, title "
        "nvarchar(256), author nvarchar(256));";

    const auto result = db.run_query(books_create);

    REQUIRE(!result.has_value());

    cleanup_db_file(db_path);
}

TEST_CASE("Insert query should be executed successfully", "[db]")
{
    spdlog::default_logger_raw()->set_level(spdlog::level::debug);

    const auto db_name = "insert_db_test"s;
    const auto db_path = db_name + ".db";
    cleanup_db_file(db_path);

    const auto db = db::database<db::sqlite_connection>{db_name};

    REQUIRE(std::filesystem::exists(db_path));

    const auto* books_create =
        "create table books (id integer primary key, title "
        "nvarchar(256), author nvarchar(256));";
    const auto* books_insert =
        "insert into books (title, author) values ('t', 'a')";
    const auto* books_select = "select * from books;";

    db.run_query(books_create);
    db.run_query(books_insert);
    db.run_query(books_insert);
    auto select_result = db.run_query(books_select);

    REQUIRE(select_result.has_value());
    REQUIRE(select_result->size() == 2);

    cleanup_db_file(db_path);
}

TEST_CASE("Should throw on invalid query", "[db]")
{
    spdlog::default_logger_raw()->set_level(spdlog::level::debug);

    const auto db_name = "throw_db_test"s;
    const auto db_path = db_name + ".db";
    cleanup_db_file(db_path);

    const auto db = db::database<db::sqlite_connection>{db_name};

    REQUIRE(std::filesystem::exists(db_path));

    const auto* invalid_query =
        "create table books o nieee (id integer primary key, title "
        "nvarchar(256), author nvarchar(256));";

    REQUIRE_THROWS(db.run_query(invalid_query));

    cleanup_db_file(db_path);
}
