#ifndef ASCIINEM_ID_POOL_HPP
#define ASCIINEM_ID_POOL_HPP

#include "server/network/types.hpp"

namespace asciinem::server::network
{

class id_pool
{
public:
    [[nodiscard]] auto next_id() noexcept -> types::id
    {
        return "null";
    }
};

} // namespace asciinem::server::network

#endif // ASCIINEM_ID_POOL_HPP
