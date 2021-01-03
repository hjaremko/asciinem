#ifndef ASCIINEM_SERVER_GAME_STATE_HPP
#define ASCIINEM_SERVER_GAME_STATE_HPP

#include "entity.hpp"
#include "player.hpp"

#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/types/variant.hpp>

namespace asciinem::server::domain
{

class game_state
{
public:
    using entities_type = std::unordered_set<player::pointer>;

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

    [[nodiscard]] auto get_entities() const -> entities_type
    {
        return entities_;
    }

    [[nodiscard]] auto find_player( const std::string& name ) const
        -> player::pointer
    {
        auto find_player = [ name ]( const auto& e ) {
            return e->get_name() == name;
        };

        auto entity_it = std::find_if(
            std::begin( entities_ ), std::end( entities_ ), find_player );

        if ( entity_it == std::end( entities_ ) )
        {
            auto msg = fmt::format( "No such entity: {}", name );
            spdlog::error( msg );
            return nullptr;
        }

        return *entity_it;
    }

private:
    entities_type entities_;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_GAME_STATE_HPP
