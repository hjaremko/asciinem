#ifndef ASCIINEM_SERVER_GAME_STATE_HPP
#define ASCIINEM_SERVER_GAME_STATE_HPP

#include "entity.hpp"

#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/utility.hpp>

namespace asciinem::server::domain
{

class game_state
{
public:
    using entities_type = std::unordered_set<entity::pointer>;

    template <class Archive>
    void save( Archive& ar ) const
    {
        ar( entities_ );
    }

    template <class Archive>
    void load( Archive& ar )
    {
        ar( entities_ );
    }

    auto get_entities() -> entities_type&
    {
        return entities_;
    }

    auto get_entities() const -> entities_type
    {
        return entities_;
    }

private:
    entities_type entities_;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_GAME_STATE_HPP
