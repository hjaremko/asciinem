#ifndef ASCIINEM_SQLITE_CONNECTION_HPP
#define ASCIINEM_SQLITE_CONNECTION_HPP

#include "query_result_type.hpp"

#include <iostream>
#include <spdlog/spdlog.h>
#include <sqlite3.h>
#include <string>
#include <utility>

namespace asciinem::server::db
{

class sqlite_connection
{
public:
    explicit sqlite_connection( std::string db_name );

    sqlite_connection( const sqlite_connection& ) = delete;
    sqlite_connection( sqlite_connection&& ) noexcept = delete;
    auto operator=( const sqlite_connection& ) -> sqlite_connection& = delete;
    auto operator=( sqlite_connection&& ) noexcept
        -> sqlite_connection& = delete;

    ~sqlite_connection();

    [[nodiscard]] auto run_query( const std::string& query ) const
        -> std::optional<types::query_result>;

private:
    [[nodiscard]] auto path() const -> std::string
    {
        return db_name_ + ".db";
    }

    [[nodiscard]] auto run_sqlite_query( const std::string& query ) const
        -> types::query_result;

    std::string db_name_;
    sqlite3* db_ { nullptr };
};

} // namespace asciinem::server::db

#endif // ASCIINEM_SQLITE_CONNECTION_HPP
