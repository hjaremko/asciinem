#ifndef ASCIINEM_SERVER_PLAYER_MAPPER_H
#define ASCIINEM_SERVER_PLAYER_MAPPER_H

#include "backpack_mapper.hpp"
#include "item_mapper.hpp"
#include "server/domain/player.hpp"
#include "server/domain/util/money.hpp"

#include <fmt/format.h>
#include <memory>
#include <server/db/query_result_type.hpp>
#include <string>

using namespace std::string_literals;

namespace asciinem::server::db
{

template <typename DB>
class player_mapper
{
public:
    explicit player_mapper( DB& db ) : db_( db )
    {
        const auto create_query = "CREATE TABLE IF NOT EXISTS players("
                                  "login VARCHAR(50) PRIMARY KEY NOT NULL,"
                                  "pos_x INT NOT NULL,"
                                  "pos_y INT NOT NULL,"
                                  "health INT NOT NULL,"
                                  "level INT NOT NULL,"
                                  "exp INT NOT NULL,"
                                  "money INT NOT NULL,"
                                  "backpack_capacity INT NOT NULL,"
                                  "weapon_name VARCHAR(50),"
                                  "armor_name VARCHAR(50),"
                                  "FOREIGN KEY (weapon_name)"
                                  "    REFERENCES items (name)"
                                  "    ON DELETE NO ACTION"
                                  "    ON UPDATE NO ACTION,"
                                  "FOREIGN KEY (armor_name)"
                                  "    REFERENCES items (name)"
                                  "    ON DELETE NO ACTION"
                                  "    ON UPDATE NO ACTION"
                                  ");"s;
        db.run_query( create_query );
    };

    auto insert( const domain::player& player ) -> void
    {
        const auto insert_query = fmt::format(
            "INSERT INTO players (login, pos_x, pos_y, health, level, exp,"
            "money, backpack_capacity) VALUES "
            "(\"{}\", {}, {}, {}, {}, {}, {}, {});",
            player.get_name(),
            player.get_position().first,
            player.get_position().second,
            player.get_health(),
            player.get_level(),
            player.get_exp(),
            int( player.get_money() ),
            player.get_backpack_capacity() );
        db_.run_query( insert_query );

        if ( player.get_weapon() )
        {
            auto update_query =
                fmt::format( "UPDATE players SET weapon_name = \"{}\" WHERE "
                             "login = \"{}\"; ",
                             player.get_weapon()->get_name(),
                             player.get_name() );
            db_.run_query( update_query );
        }
        if ( player.get_armor() )
        {
            auto update_query =
                fmt::format( "UPDATE players SET armor_name = \"{}\" WHERE "
                             "login = \"{}\"; ",
                             player.get_weapon()->get_name(),
                             player.get_name() );
            db_.run_query( update_query );
        }

        auto bm = backpack_mapper( db_ );
        bm.insert_player_backpack( player.get_name(), player.get_backpack() );
    }

    auto update( const domain::player& player ) -> void
    {
        auto update_query =
            fmt::format( "UPDATE players SET pos_x = {}, pos_y = {}, "
                         "health = {}, level = {}, exp = {}, money = {}, "
                         "backpack_capacity = {}, weapon_name = null, "
                         "armor_name = null WHERE login = \"{}\"; ",
                         player.get_position().first,
                         player.get_position().second,
                         player.get_health(),
                         player.get_level(),
                         player.get_exp(),
                         int( player.get_money() ),
                         player.get_backpack_capacity(),
                         player.get_name() );
        db_.run_query( update_query );

        if ( player.get_weapon() )
        {
            update_query =
                fmt::format( "UPDATE players SET weapon_name = \"{}\" WHERE "
                             "login = \"{}\"; ",
                             player.get_weapon()->get_name(),
                             player.get_name() );
            db_.run_query( update_query );
        }

        if ( player.get_armor() )
        {
            update_query =
                fmt::format( "UPDATE players SET armor_name = \"{}\" WHERE "
                             "login = \"{}\"; ",
                             player.get_weapon()->get_name(),
                             player.get_name() );
            db_.run_query( update_query );
        }

        auto bm = backpack_mapper( db_ );
        bm.remove_all_for_player( player.get_name() );
        bm.insert_player_backpack( player.get_name(), player.get_backpack() );
    }

    auto find( std::string login )
    {
        const auto find_query =
            fmt::format( "SELECT * FROM players WHERE login = \"{}\";", login );
        auto result = db_.run_query( find_query );
        if ( result.has_value() )
        {
            spdlog::debug( "Found player {} in the database!", login );
            auto record = *result->begin();
            return record_to_player( record );
        }

        spdlog::debug( "Player {} logged for the first time!", login );

        auto im = item_mapper( db_ );
        auto stick = ( im.record_to_weapon( im.find_by_name( "stick" ) ) );
        auto apple = im.record_to_potion( im.find_by_name( "apple" ) );

        auto player = std::make_shared<domain::player>( login );
        player->add_to_backpack( stick );
        player->add_to_backpack( apple );

        insert( *player );
        return player;
    }

    auto remove( const domain::player& player ) -> void
    {
        const auto delete_player_query = fmt::format(
            "DELETE FROM players WHERE login = \"{}\";", player.get_name() );
        db_.run_query( delete_player_query );
    }

    [[nodiscard]] auto record_to_player( types::record record ) const
        -> domain::player::pointer
    {
        auto name =
            std::find_if( std::begin( record ),
                          std::end( record ),
                          []( const auto& p ) { return p.first == "login"; } )
                ->second;
        auto pos_x =
            std::find_if( std::begin( record ),
                          std::end( record ),
                          []( const auto& p ) { return p.first == "pos_x"; } )
                ->second;
        auto pos_y =
            std::find_if( std::begin( record ),
                          std::end( record ),
                          []( const auto& p ) { return p.first == "pos_y"; } )
                ->second;
        auto health =
            std::find_if( std::begin( record ),
                          std::end( record ),
                          []( const auto& p ) { return p.first == "health"; } )
                ->second;
        auto level =
            std::find_if( std::begin( record ),
                          std::end( record ),
                          []( const auto& p ) { return p.first == "level"; } )
                ->second;
        auto exp =
            std::find_if( std::begin( record ),
                          std::end( record ),
                          []( const auto& p ) { return p.first == "exp"; } )
                ->second;
        auto money =
            std::find_if( std::begin( record ),
                          std::end( record ),
                          []( const auto& p ) { return p.first == "money"; } )
                ->second;
        auto backpack_capacity =
            std::find_if(
                std::begin( record ),
                std::end( record ),
                []( const auto& p ) { return p.first == "backpack_capacity"; } )
                ->second;

        auto weapon_name = std::find_if( std::begin( record ),
                                         std::end( record ),
                                         []( const auto& p ) {
                                             return p.first == "weapon_name";
                                         } )
                               ->second;

        auto weapon = domain::weapon::pointer {};

        if ( weapon_name )
        {
            auto im = item_mapper( db_ );
            weapon = im.record_to_weapon( im.find_by_name( *weapon_name ) );
        }

        auto armor_name = std::find_if( std::begin( record ),
                                        std::end( record ),
                                        []( const auto& p ) {
                                            return p.first == "armor_name";
                                        } )
                              ->second;

        auto armor = domain::armor::pointer {};

        if ( armor_name )
        {
            auto im = item_mapper( db_ );
            armor = im.record_to_armor( im.find_by_name( *armor_name ) );
        }

        auto bm = backpack_mapper( db_ );
        auto backpack = bm.get_backpack_for_player( *name );
        return std::make_shared<domain::player>(
            *name,
            std::make_pair( std::stoi( *pos_x ), std::stoi( *pos_y ) ),
            std::stoi( *health ),
            std::stoi( *level ),
            std::stoi( *exp ),
            double( std::stoi( *money ) ) / domain::money::SCALE(),
            backpack,
            std::stoi( *backpack_capacity ),
            weapon,
            armor );
    }

private:
    DB& db_;
};

} // namespace asciinem::server::db
#endif // ASCIINEM_SERVER_PLAYER_MAPPER_H
