#include "db/sqlite_connection.hpp"

namespace
{
using namespace asciinem::server::db;

auto make_key_value( int i, char** record_data, char** col_name )
{
    auto make_value = [ i, record_data ] {
        return record_data[ i ]                             // NOLINT
                   ? std::make_optional( record_data[ i ] ) // NOLINT
                   : std::nullopt;
    };

    return std::make_pair( col_name[ i ], make_value() ); // NOLINT
}

auto to_query_result( void* result )
{
    return static_cast<types::query_result*>( result );
}

auto callback( void* result,
               int record_amount,
               char** record_data,
               char** col_name ) -> int
{
    using namespace asciinem::server::db;

    spdlog::trace( "Columns: {}", record_amount );

    auto* table = to_query_result( result );
    auto record = types::record {};

    for ( int i = 0; i < record_amount; i++ )
    {
        record.insert( make_key_value( i, record_data, col_name ) );
    }

    table->insert( record );

    return 0;
}

void check_errors( int rc, char* sqlite_err_msg, const std::string& query )
{
    if ( sqlite_err_msg )
    {
        auto error_msg = std::string { sqlite_err_msg };
        spdlog::error( error_msg );
        sqlite3_free( sqlite_err_msg );
        throw std::runtime_error( error_msg );
    }

    if ( rc != SQLITE_OK )
    {
        const auto error_msg = fmt::format( "Error executing `{}`", query );
        spdlog::error( error_msg );
        throw std::runtime_error( error_msg );
    }
}

} // namespace

namespace asciinem::server::db
{

sqlite_connection::sqlite_connection( std::string db_name )
    : db_name_( std::move( db_name ) )
{
    spdlog::info( "Connecting to database {}...", db_name_ );

    const auto db_path = path();
    const auto rc = sqlite3_open( db_path.c_str(), &db_ );

    if ( rc != SQLITE_OK )
    {
        auto error_msg = "Can't open database " + db_path;
        spdlog::error( error_msg );
        throw std::runtime_error( error_msg ); // todo: custom db exception
    }

    spdlog::info( "Opened database {} successfully", db_path );
}

sqlite_connection::~sqlite_connection()
{
    spdlog::info( "Closing connection to database {}...", db_name_ );

    const auto rc = sqlite3_close( db_ );

    if ( rc != SQLITE_OK )
    {
        spdlog::error( "Can't close database {}", db_name_ );
    }

    spdlog::info( "Closed database successfully" );
}

auto sqlite_connection::run_sqlite_query( const std::string& query ) const
    -> types::query_result
{
    auto result = types::query_result {};

    char* sqlite_err_msg = nullptr;
    const auto rc =
        sqlite3_exec( db_, query.c_str(), callback, &result, &sqlite_err_msg );

    check_errors( rc, sqlite_err_msg, query );

    return result;
}

auto sqlite_connection::run_query( const std::string& query ) const
    -> std::optional<types::query_result>
{
    spdlog::debug( "Running query: `{}` on {}", query, db_name_ );

    auto result = run_sqlite_query( query );

    spdlog::debug( "Query: `{}` on {} executed successfully", query, db_name_ );
    spdlog::debug( "Selected {} records.", result.size() );

    return result.empty() ? std::nullopt : std::make_optional( result );
}

} // namespace asciinem::server::db
