#ifndef ASCIINEM_QUERY_RESULT_TYPE_HPP
#define ASCIINEM_QUERY_RESULT_TYPE_HPP

#include <iostream>
#include <set>
#include <spdlog/spdlog.h>
#include <unordered_set>

namespace asciinem::server::db
{

namespace types
{

using record = std::set<std::pair<std::string, std::optional<std::string>>>;
using query_result = std::set<record>;

} // namespace types

[[maybe_unused]] inline void print_query_result( const types::query_result& r )
{
    for ( const auto& record : r )
    {
        auto rs = std::string {};

        for ( const auto& tup : record )
        {
            rs += fmt::format(
                "{} = {}, ", tup.first, tup.second.value_or( "null" ) );
        }

        fmt::print( "{}\n", rs );
    }
}

} // namespace asciinem::server::db

#endif // ASCIINEM_QUERY_RESULT_TYPE_HPP
