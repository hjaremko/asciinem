#ifndef ASCIINEM_SERVER_CONFIG_HPP
#define ASCIINEM_SERVER_CONFIG_HPP

#include "types.hpp"

namespace asciinem::server::network
{

struct server_config // NOLINT
{
    types::port port;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_SERVER_CONFIG_HPP
