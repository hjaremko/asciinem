#ifndef ASCIINEM_SERVER_CONFIG_HPP
#define ASCIINEM_SERVER_CONFIG_HPP

#include "types.hpp"

namespace asciinem::server::network
{

struct server_config // NOLINT
{
    types::ip ip;
    types::port port;
};

inline static const auto default_config = // NOLINT
    server_config { "localhost", 5555 };

} // namespace asciinem::server::network

#endif // ASCIINEM_SERVER_CONFIG_HPP
