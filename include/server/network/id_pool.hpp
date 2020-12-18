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
        return id_++;
    }

private:
    types::id id_ { 0 };
};

} // namespace asciinem::server::network

#endif // ASCIINEM_ID_POOL_HPP
