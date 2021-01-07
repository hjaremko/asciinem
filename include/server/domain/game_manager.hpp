#ifndef ASCIINEM_SERVER_GAME_MANAGER_HPP
#define ASCIINEM_SERVER_GAME_MANAGER_HPP

#include "collision_checker.hpp"
#include "fight_manager.hpp"
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
    game_manager()
    {
        current_state_.spawn_boss( { 73, 3 } );
    }

    [[nodiscard]] auto get_state() const -> game_state
    {
        return current_state_;
    }

    void move_player( const std::string& login,
                      const entity::position_type& offset )
    {
        auto player = current_state_.find_player( login );
        auto new_position = player->get_position();

        new_position.first += offset.first;
        new_position.second += offset.second;

        auto monster_collision = false;
        for ( const auto& m : current_state_.get_monsters() )
        {
            if ( collision_checker::check_collision(
                     new_position,
                     static_cast<int>( player->get_shape().length() ),
                     m->get_position(),
                     static_cast<int>( m->get_shape().length() ) ) )
            {
                monster_collision = true;
                break;
            }
        }

        if ( !monster_collision &&
             !collision_checker::check_collision(
                 new_position,
                 static_cast<int>( player->get_shape().length() ),
                 current_state_.get_location() ) )
        {
            player->set_position( new_position );
        }
    }

    void fight( const std::string& login )
    {
        auto player = current_state_.find_player( login );
        auto monsters = current_state_.get_monsters();

        for ( const auto& m : monsters )
        {
            if ( is_near( player, m ) )
            {
                spdlog::warn(
                    fmt::format( "Player {} got in a fight with monster {}",
                                 player->get_name(),
                                 m->get_name() ) );

                fight_manager::fight( *player, *m );

                if ( m->is_dead() )
                {
                    auto exp = 15 * m->get_level(); // NOLINT
                    auto level_up = player->gain_exp( exp );
                    player->add_to_backpack(
                        item_mapper_.get_item_on_level( m->get_level() ) );

                    if ( level_up )
                    {
                        spdlog::warn( "Player won" );
                        current_state_.set_notice( fmt::format(
                            "Player {} has won a fight and leveled up!",
                            login,
                            exp ) );
                    }
                    else
                    {
                        spdlog::warn( "Player won" );
                        current_state_.set_notice( fmt::format(
                            "Player {} has won a fight and gained {} EXP!",
                            login,
                            exp ) );
                    }
                }
                else
                {
                    spdlog::warn( "Player lost" );
                    current_state_.set_notice( fmt::format(
                        "Player {} has lost a fight! Respawning...", login ) );
                    player->reset();
                }

                break;
            }
        }

        remove_dead_monsters();
    }

    void use( const std::string& login, int ind )
    {
        spdlog::warn( fmt::format( "Player {} uses item {}.", login, ind ) );
        auto player = current_state_.find_player( login );
        auto bp = std::vector<server::domain::item::pointer> {};

        for ( const auto& p : player->get_backpack() )
        {
            bp.push_back( p );
        }

        std::sort( bp.begin(), bp.end(), []( auto a, auto b ) {
            return a->get_name() < b->get_name();
        } );

        if ( ind < static_cast<int>( bp.size() ) )
        {
            auto i = bp[ ind ];
            i->use( *player );
        }
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

    void remove_dead_monsters()
    {
        auto& monsters = current_state_.get_monsters();

        for ( auto it = monsters.begin(); it != monsters.end(); )
        {
            if ( ( *it )->is_dead() )
            {
                it = monsters.erase( it );
            }
            else
            {
                ++it;
            }
        }
    }

    void tick()
    {
        ++ticks_;

        if ( ticks_ % 70 == 0 )
        {
            move_monsters();
        }

        if ( ticks_ % 1000 == 0 && current_state_.get_monsters().size() < 3 )
        {
            current_state_.spawn_monster( { 18, 10 } );
        }

        if ( ticks_ % 800 == 0 )
        {
            current_state_.clear_notice();
        }
    }

private:
    void move_monsters()
    {
        for ( const auto& m : current_state_.get_monsters() )
        {
            auto [ mx, my ] = m->move();
            auto [ x, y ] = m->get_position();
            auto new_position = entity::position_type { x + mx, y + my };

            auto entity_collision = false;
            for ( const auto& e : current_state_.get_entities() )
            {
                if ( collision_checker::check_collision(
                         new_position,
                         static_cast<int>( m->get_shape().length() ),
                         e->get_position(),
                         static_cast<int>( e->get_shape().length() ) ) )
                {
                    entity_collision = true;
                    break;
                }
            }

            if ( !entity_collision &&
                 !collision_checker::check_collision(
                     new_position,
                     static_cast<int>( m->get_shape().length() ),
                     current_state_.get_location() ) )
            {
                m->set_position( new_position );
            }
        }
    }

    static auto is_near( const entity::pointer& first,
                         const entity::pointer& second ) -> bool
    {
        auto dist_x = 0;

        auto a = first->get_position().first;
        auto b = a + static_cast<int>( first->get_shape().length() ) - 1;

        auto c = second->get_position().first;
        auto d = c + static_cast<int>( second->get_shape().length() ) - 1;

        if ( b < c )
        {
            dist_x = abs( b - c );
        }
        else if ( d < a )
        {
            dist_x = abs( d - a );
        }

        auto dist_y =
            abs( first->get_position().second - second->get_position().second );

        return dist_x <= 1 && dist_y <= 1;
    }

    using db_server = db::sqlite_connection;
    using db_type = db::database<db_server>;

    game_state current_state_;
    db_type db_ { "asciinem" };
    db::item_mapper<db_type> item_mapper_ { db_ };
    db::player_mapper<db_type> player_mapper_ { db_ };
    unsigned long long ticks_ { 0 };
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_GAME_MANAGER_HPP
