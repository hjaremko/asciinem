#ifndef ASCIINEM_SERVER_UTIL_HPP
#define ASCIINEM_SERVER_UTIL_HPP

#include "server/network/types.hpp"

#include <cxxopts.hpp>
#include <spdlog/spdlog.h>

namespace asciinem::server
{

auto parse_command_line(int argc, char** argv) -> cxxopts::ParseResult;
auto get_log_level(const cxxopts::ParseResult& result)
    -> spdlog::level::level_enum;
auto get_port(const cxxopts::ParseResult& result) -> network::types::port;

} // namespace asciinem::server

#endif // ASCIINEM_SERVER_UTIL_HPP
