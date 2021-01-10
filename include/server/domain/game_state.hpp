#ifndef ASCIINEM_SERVER_GAME_STATE_HPP
#define ASCIINEM_SERVER_GAME_STATE_HPP

#include "entity.hpp"
#include "location.hpp"
#include "monster.hpp"
#include "player.hpp"

#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/unordered_set.hpp>

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

    auto get_entities() -> players_type&;
    [[nodiscard]] auto get_entities() const -> players_type;
    auto get_monsters() -> monsters_type&;
    [[nodiscard]] auto get_monsters() const -> monsters_type;
    auto get_notice() -> std::string&;
    [[nodiscard]] auto get_notice() const -> std::string;
    void set_notice( const std::string& notice );
    void clear_notice();
    [[nodiscard]] auto find_player( const std::string& name ) const
        -> player::pointer;
    void spawn_monster( entity::position_type where );
    void spawn_boss( entity::position_type where );
    [[nodiscard]] auto get_map() const -> std::vector<std::string>;
    [[nodiscard]] auto get_location() const -> location;

private:
    players_type entities_;
    monsters_type monsters_;
    location map_ { "map1.txt", "map1_collisions.txt" };
    std::string notice_;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_GAME_STATE_HPP
