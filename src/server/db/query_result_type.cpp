#include "server/db/query_result_type.hpp"

#include <fmt/format.h>

namespace asciinem::server::db
{

[[maybe_unused]] void print_query_result( const types::query_result& r )
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
