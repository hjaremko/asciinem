#ifndef ASCIINEM_QUERY_RESULT_TYPE_HPP
#define ASCIINEM_QUERY_RESULT_TYPE_HPP

#include <optional>
#include <set>
#include <unordered_set>

namespace asciinem::server::db
{

namespace types
{

using record = std::set<std::pair<std::string, std::optional<std::string>>>;
using query_result = std::set<record>;

} // namespace types

[[maybe_unused]] inline void print_query_result( const types::query_result& r );

} // namespace asciinem::server::db

#endif // ASCIINEM_QUERY_RESULT_TYPE_HPP
