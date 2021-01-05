#ifndef ASCIINEM_SERVER_GAME_MANAGER_HPP
#define ASCIINEM_SERVER_GAME_MANAGER_HPP

#include "game_state.hpp"
#include "player.hpp"
#include "server/db/database.hpp"
#include "server/db/mappers/player_mapper.hpp"
#include "server/db/sqlite_connection.hpp"

#include <algorithm>

namespace asciinem::server::domain
{

class game_manager
{
public:
    [[nodiscard]] auto get_state() const -> game_state
    {
        return current_state_;
    }

    void move_player( const std::string& login,
                      const entity::position_type& offset )
    {
        auto player = current_state_.find_player( login );
        auto pos = player->get_position();

        pos.first += offset.first;
        pos.second += offset.second;

        player->set_position( pos );
    }

    void add_player( const std::string& login )
    {
        auto player = player_mapper_.find( login );
        current_state_.get_entities().insert( player );
    }

    void remove_player( const std::string& login )
    {
        auto player = current_state_.find_player( login );
        auto& entities = current_state_.get_entities();

        for ( auto it = entities.begin(); it != entities.end(); )
        {
            if ( ( *it )->get_name() == player->get_name() )
            {
                it = entities.erase( it );
            }
            else
            {
                ++it;
            }
        }

        player_mapper_.update( *player );
    }

    void tick()
    {
        ++ticks_;

        if ( ticks_ % 10 == 0 )
        {
            update_monsters();
        }

        if ( ticks_ % 1000 == 0 )
        {
            current_state_.spawn_monsters();
        }
    }

private:
    void update_monsters()
    {
        for ( const auto& m : current_state_.get_monsters() )
        {
            auto [ mx, my ] = m->move();
            auto [ x, y ] = m->get_position();
            m->set_position( { x + mx, y + my } );
        }
    }

    using db_server = db::sqlite_connection;
    using db_type = db::database<db_server>;

    game_state current_state_;
    db_type db_ { "asciinem" };
    db::item_mapper<db_type> item_mapper_ { db_ };
    db::player_mapper<db_type> player_mapper_ { db_ };
    //    db::backpack_mapper<db_type> backpack_mapper_ { db_ };
    unsigned long long ticks_ { 0 };
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_GAME_MANAGER_HPP
