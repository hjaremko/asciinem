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
                                  "money INT NOT NULL,"
                                  "backpack_capacity INT NOT NULL,"
                                  "weapon_id INTEGER,"
                                  "armor_id INTEGER,"
                                  "FOREIGN KEY (weapon_id)"
                                  "    REFERENCES items (item_id)"
                                  "    ON DELETE NO ACTION"
                                  "    ON UPDATE NO ACTION,"
                                  "FOREIGN KEY (armor_id)"
                                  "    REFERENCES items (item_id)"
                                  "    ON DELETE NO ACTION"
                                  "    ON UPDATE NO ACTION"
                                  ");"s;
        db.run_query( create_query );
    };

    auto insert( const domain::player& player ) -> void
    {
        const auto insert_query = fmt::format(
            "INSERT INTO players (login, pos_x, pos_y, health, level, "
            "money, backpack_capacity, weapon_id, armor_id) VALUES (\"{}\", "
            "{}, {}, {}, {}, {}, {}, {}, {});",
            player.get_name(),
            player.get_position().first,
            player.get_position().second,
            player.get_health(),
            player.get_level(),
            int( player.get_money() ),
            player.get_backpack_capacity(),
            ( player.get_weapon()
                  ? fmt::to_string( player.get_weapon()->get_id() )
                  : "NULL" ),
            ( player.get_armor()
                  ? fmt::to_string( player.get_armor()->get_id() )
                  : "NULL" ) );
        db_.run_query( insert_query );

        auto bm = backpack_mapper( db_ );
        bm.insert_player_backpack( player.get_name(), player.get_backpack() );
    }

    auto update( const domain::player& player ) -> void
    {
        const auto update_query = fmt::format(
            "UPDATE players SET pos_x = {}, pos_y = {}, "
            "health = {}, level = {}, money = {}, backpack_capacity = {}, "
            "weapon_id = {}, armor_id = {} WHERE login = \"{}\"; ",
            player.get_position().first,
            player.get_position().second,
            player.get_health(),
            player.get_level(),
            int( player.get_money() ),
            player.get_backpack_capacity(),
            ( player.get_weapon()
                  ? fmt::to_string( player.get_weapon()->get_id() )
                  : "NULL" ),
            ( player.get_armor()
                  ? fmt::to_string( player.get_armor()->get_id() )
                  : "NULL" ),
            player.get_name() );
        db_.run_query( update_query );

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
        auto player = std::make_shared<domain::player>( login );
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

        auto weapon_id = std::find_if( std::begin( record ),
                                       std::end( record ),
                                       []( const auto& p ) {
                                           return p.first == "weapon_id";
                                       } )
                             ->second;

        auto weapon = domain::item::pointer {};

        if ( weapon_id )
        {
            auto im = item_mapper( db_ );
            weapon =
                //                std::dynamic_pointer_cast<domain::weapon>(
                im.record_to_item(
                    im.find_by_id( std::stoi( *weapon_id ) ) ); //);
        }

        auto armor_id = std::find_if( std::begin( record ),
                                      std::end( record ),
                                      []( const auto& p ) {
                                          return p.first == "armor_id";
                                      } )
                            ->second;

        auto armor = domain::item::pointer {};

        if ( armor_id )
        {
            auto im = item_mapper( db_ );
            armor =
                //                std::dynamic_pointer_cast<domain::armor>(
                im.record_to_item( im.find_by_id( std::stoi( *armor_id ) ) );
            //                );
        }

        auto bm = backpack_mapper( db_ );
        auto b = bm.get_backpack_for_player( *name );

        return std::make_shared<domain::player>(
            *name,
            std::make_pair( std::stoi( *pos_x ), std::stoi( *pos_y ) ),
            std::stoi( *health ),
            std::stoi( *level ),
            double( std::stoi( *money ) ) / domain::money::SCALE(),
            std::set<domain::item::pointer> {},
            std::stoi( *backpack_capacity ),
            weapon,
            armor );
    }

private:
    DB& db_;
};

} // namespace asciinem::server::db
#endif // ASCIINEM_SERVER_PLAYER_MAPPER_H
