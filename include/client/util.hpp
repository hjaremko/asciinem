#ifndef ASCIINEM_SERVER_UTIL_HPP
#define ASCIINEM_SERVER_UTIL_HPP

#include "server/network/types.hpp"

#include <cxxopts.hpp>
#include <spdlog/spdlog.h>

namespace asciinem::client
{

auto parse_command_line( int argc, char** argv ) -> cxxopts::ParseResult;
auto get_log_level( const cxxopts::ParseResult& result )
    -> spdlog::level::level_enum;
auto get_port( const cxxopts::ParseResult& result )
    -> server::network::types::port;
auto get_ip( const cxxopts::ParseResult& result ) -> server::network::types::ip;
auto get_login( const cxxopts::ParseResult& result ) -> std::string;

} // namespace asciinem::client

#endif // ASCIINEM_SERVER_UTIL_HPP
