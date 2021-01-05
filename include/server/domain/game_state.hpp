#ifndef ASCIINEM_SERVER_GAME_STATE_HPP
#define ASCIINEM_SERVER_GAME_STATE_HPP

#include "entity.hpp"
#include "monster.hpp"
#include "player.hpp"

#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>
#include <cereal/types/utility.hpp>
#include <spdlog/spdlog.h>
#include <utility>

namespace asciinem::server::domain
{

class game_state
{
public:
    using players_type = std::unordered_set<player::pointer>;
    using monsters_type = std::unordered_set<monster::pointer>;

    template <class Archive>
    void save( Archive& ar ) const
    {
        ar( entities_, monsters_ );
    }

    template <class Archive>
    void load( Archive& ar )
    {
        ar( entities_, monsters_ );
    }

    auto get_entities() -> players_type&
    {
        return entities_;
    }

    [[nodiscard]] auto get_entities() const -> players_type
    {
        return entities_;
    }

    auto get_monsters() -> monsters_type&
    {
        return monsters_;
    }

    [[nodiscard]] auto get_monsters() const -> monsters_type
    {
        return monsters_;
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
            spdlog::warn( msg );
            return nullptr;
        }

        return *entity_it;
    }

    void spawn_monster()
    {
        monsters_.insert( std::make_shared<monster>(
            "mob", entity::position_type { 10, 10 }, 150, 2 ) );
    }

private:
    players_type entities_;
    monsters_type monsters_;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_GAME_STATE_HPP
