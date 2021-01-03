#ifndef ASCIINEM_SERVER_ITEM_MAPPER_H
#define ASCIINEM_SERVER_ITEM_MAPPER_H

#include "server/domain/armor.hpp"
#include "server/domain/item.hpp"
#include "server/domain/weapon.hpp"

#include <fmt/format.h>
#include <server/db/query_result_type.hpp>

using namespace std::string_literals;

namespace asciinem::server::db
{

template <typename DB>
class item_mapper
{
public:
    explicit item_mapper( DB& db ) : db_( db )
    {
        const auto create_query =
            "CREATE TABLE IF NOT EXISTS items("
            "item_id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            "name VARCHAR(50) NOT NULL,"
            "value INT NOT NULL,"
            "level INT NOT NULL,"
            "defense INT NOT NULL,"
            "attack INT NOT NULL);"s;
        db_.run_query( create_query );
    };

    auto update_impl( const domain::item& item ) -> bool
    {
        const auto update_query = fmt::format(
            "UPDATE items SET name = \"{}\", value = {}, level = {}, "
            "defense = 0, attack = 0 WHERE item_id = {}",
            item.get_name(),
            item.get_value(),
            item.get_level(),
            item.get_id() );
        db_.run_query( update_query );

        return true;
    }

    auto update( const domain::item& item ) -> bool
    {
        return update_impl( item );
    }

    auto update( const domain::weapon& weapon ) -> bool
    {
        update_impl( weapon );
        db_.run_query(
            fmt::format( "UPDATE items SET attack = {} WHERE item_id = {}",
                         weapon.get_attack(),
                         weapon.get_id() ) );
        return true;
    }

    auto update( const domain::armor& armor ) -> bool
    {
        update_impl( armor );
        db_.run_query(
            fmt::format( "UPDATE items SET defense = {} WHERE item_id = {}",
                         armor.get_defense(),
                         armor.get_id() ) );
        return true;
    }

    auto remove( const domain::item& item ) -> bool
    {
        const auto delete_item = fmt::format(
            "DELETE FROM items WHERE item_id = {};", item.get_id() );
        db_.run_query( delete_item );

        return true;
    }

    auto find_by_id( int item_id ) -> types::record
    {
        const auto find_query =
            fmt::format( "SELECT * FROM items WHERE item_id = {};", item_id );
        auto result = db_.run_query( find_query );
        return *result->begin();
    }

    [[nodiscard]] auto record_to_item( types::record record )
        -> domain::item::pointer
    {
        auto id =
            std::find_if( std::begin( record ),
                          std::end( record ),
                          []( const auto& p ) { return p.first == "item_id"; } )
                ->second;
        auto name =
            std::find_if( std::begin( record ),
                          std::end( record ),
                          []( const auto& p ) { return p.first == "name"; } )
                ->second;
        auto value =
            std::find_if( std::begin( record ),
                          std::end( record ),
                          []( const auto& p ) { return p.first == "value"; } )
                ->second;
        auto level =
            std::find_if( std::begin( record ),
                          std::end( record ),
                          []( const auto& p ) { return p.first == "level"; } )
                ->second;
        auto defense =
            std::find_if( std::begin( record ),
                          std::end( record ),
                          []( const auto& p ) { return p.first == "defense"; } )
                ->second;
        auto attack =
            std::find_if( std::begin( record ),
                          std::end( record ),
                          []( const auto& p ) { return p.first == "attack"; } )
                ->second;

        if ( defense )
        {
            return std::make_shared<domain::armor>( std::stoi( *id ),
                                                    *name,
                                                    std::stoi( *value ),
                                                    std::stoi( *level ),
                                                    std::stoi( *defense ) );
        }
        if ( attack )
        {
            return std::make_shared<domain::weapon>( std::stoi( *id ),
                                                     *name,
                                                     std::stoi( *value ),
                                                     std::stoi( *level ),
                                                     std::stoi( *attack ) );
        }
        return std::make_shared<domain::item>(
            std::stoi( *id ), *name, std::stoi( *value ), std::stoi( *level ) );
    }

private:
    DB& db_;
};

} // namespace asciinem::server::db

#endif // ASCIINEM_SERVER_ITEM_MAPPER_H
