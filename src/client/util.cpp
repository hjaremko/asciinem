#include "client/util.hpp"

namespace asciinem::client
{

auto parse_command_line( int argc, char** argv ) -> cxxopts::ParseResult
{
    using namespace cxxopts;

    static auto options { Options { *argv, "Asciinem client 1.0.0" } };
    options.positional_help( "[optional args]" ).show_positional_help();

    options.add_options()( "h,help", "Print usage" )(
        "l,login", "Set user login", value<std::string>() )(
        "p,port", "Set server port", value<int>()->default_value( "5555" ) )(
        "i,ip",
        "Set server ip",
        value<std::string>()->default_value( "localhost" ) )(
        "v,verbose",
        "Set logging level",
        value<std::string>()->default_value( "info" )->implicit_value(
            "debug" ) );

    auto result = options.parse( argc, argv );

    if ( result.count( "help" ) )
    {
        fmt::print( "{}\n", options.help( { "", "Group" } ) );
        std::exit( 0 );
    }

    return result;
}

auto get_log_level( const cxxopts::ParseResult& result )
    -> spdlog::level::level_enum
{
    auto level = result[ "verbose" ].as<std::string>();

    if ( level == "debug" )
    {
        return spdlog::level::debug;
    }

    if ( level == "trace" )
    {
        return spdlog::level::trace;
    }

    return spdlog::level::info;
}

auto get_port( const cxxopts::ParseResult& result )
    -> server::network::types::port
{
    return static_cast<unsigned short>( result[ "port" ].as<int>() );
}

auto get_ip( const cxxopts::ParseResult& result ) -> server::network::types::ip
{
    return result[ "ip" ].as<std::string>();
}

auto get_login( const cxxopts::ParseResult& result ) -> std::string
{
    return result[ "login" ].as<std::string>();
}

} // namespace asciinem::client
