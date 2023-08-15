#ifndef ASCIINEM_SERVER_GAME_STATE_HPP
#define ASCIINEM_SERVER_GAME_STATE_HPP

#include "entity.hpp"
#include "location.hpp"
#include "monster.hpp"
#include "player.hpp"
#include "strategies/still_strategy.hpp"

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
    void serialize( Archive& ar )
    {
        ar( entities_, monsters_, map_, notice_ );
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

    auto get_notice() -> std::string&
    {
        return notice_;
    }

    [[nodiscard]] auto get_notice() const -> std::string
    {
        return notice_;
    }

    void set_notice( const std::string& notice )
    {
        notice_ = notice;
    }

    void clear_notice()
    {
        notice_ = "";
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
            spdlog::debug( msg );
            return nullptr;
        }

        return *entity_it;
    }

    void spawn_monster( entity::position_type where )
    {
        monsters_.insert( std::make_shared<monster>( "mob", where, 150, 1 ) );
    }

    void spawn_boss( entity::position_type where )
    {
        auto boss =
            std::make_shared<monster>( "wonsz rzeczny",
                                       where,
                                       200,
                                       5,
                                       std::make_shared<still_strategy>() );
        boss->set_shape( "~~~~O<" );
        monsters_.insert( std::move( boss ) );
    }

    [[nodiscard]] auto get_map() const -> std::vector<std::string>
    {
        return map_.get_map();
    }

    [[nodiscard]] auto get_location() const -> location
    {
        return map_;
    }

private:
    players_type entities_;
    monsters_type monsters_;
    location map_ { "locations/map1.txt",
                    "locations/map1_collisions.txt" }; // todo
    std::string notice_;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_GAME_STATE_HPP
