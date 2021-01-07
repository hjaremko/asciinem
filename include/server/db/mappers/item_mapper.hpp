#ifndef ASCIINEM_SERVER_ITEM_MAPPER_H
#define ASCIINEM_SERVER_ITEM_MAPPER_H

#include "server/domain/armor.hpp"
#include "server/domain/health_potion.hpp"
#include "server/domain/item.hpp"
#include "server/domain/weapon.hpp"

#include <fmt/format.h>
#include <random>
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
        const auto create_query = "CREATE TABLE IF NOT EXISTS items("
                                  "name VARCHAR(50) PRIMARY KEY NOT NULL,"
                                  "value INT NOT NULL,"
                                  "level INT NOT NULL,"
                                  "defense INT,"
                                  "attack INT,"
                                  "power INT);"s;
        db_.run_query( create_query );

        auto table_empty = !db_.run_query( "SELECT * FROM items;" ).has_value();
        if ( table_empty )
        {
            const auto items_query =
                "INSERT INTO items(name, value, level, "
                "defense, attack, power) VALUES"
                "(\"stick\", 10, 1, null, 1, null),"
                "(\"apple\", 10, 1, null, null, 10),"
                "(\"wooden armor\", 25, 2, 2, null, null),"
                "(\"wooden sword\", 30, 2, null, 2, null),"
                "(\"common potion\", 25, 2, null, null, 50),"
                "(\"steel armor\", 55, 3, 10, null, null),"
                "(\"steel sword\", 65, 3, null, 10, null),"
                "(\"rare potion\", 70, 3, null, null, 100);"s;
            db_.run_query( items_query );
        }
    };

    auto insert_impl( const domain::item& item ) -> void
    {
        const auto items_query = fmt::format(
            "INSERT INTO items(name, value, level) VALUES (\"{}\", {}, {})",
            item.get_name(),
            int( item.get_value() ),
            item.get_level() );
        db_.run_query( items_query );
    }

    auto insert( const domain::item& item ) -> void
    {
        insert_impl( item );
    }

    auto insert( const domain::weapon& weapon ) -> void
    {
        insert_impl( weapon );
        const auto items_query =
            fmt::format( "UPDATE item SET attack = {} WHERE name = \"{}\"",
                         weapon.get_attack(),
                         weapon.get_name() );
        db_.run_query( items_query );
    }

    auto insert( const domain::armor& armor ) -> void
    {
        insert_impl( armor );
        const auto items_query =
            fmt::format( "UPDATE items SET defense = {} WHERE name = \"{}\"",
                         armor.get_defense(),
                         armor.get_name() );
        db_.run_query( items_query );
    }

    auto insert( const domain::health_potion& potion ) -> void
    {
        insert_impl( potion );
        const auto items_query =
            fmt::format( "UPDATE item SET power = {} WHERE name = \"{}\"",
                         potion.get_power(),
                         potion.get_name() );
        db_.run_query( items_query );
    }

    auto update_impl( const domain::item& item ) -> void
    {
        const auto update_query = fmt::format(
            "UPDATE items SET value = {}, level = {}, defense = "
            "null, attack = null, power = null WHERE name = \"{}\";",
            int( item.get_value() ),
            item.get_level(),
            item.get_name() );
        db_.run_query( update_query );
    }

    auto update( const domain::item& item ) -> void
    {
        update_impl( item );
    }

    auto update( const domain::weapon& weapon ) -> void
    {
        update_impl( weapon );
        db_.run_query(
            fmt::format( "UPDATE items SET attack = {} WHERE name = \"{}\";",
                         weapon.get_attack(),
                         weapon.get_name() ) );
    }

    auto update( const domain::armor& armor ) -> void
    {
        update_impl( armor );
        db_.run_query(
            fmt::format( "UPDATE items SET defense = {} WHERE name = \"{}\";",
                         armor.get_defense(),
                         armor.get_name() ) );
    }

    auto update( const domain::health_potion& potion ) -> void
    {
        update_impl( potion );
        db_.run_query(
            fmt::format( "UPDATE items SET power = {} WHERE name = \"{}\"",
                         potion.get_power(),
                         potion.get_name() ) );
    }

    auto remove( const domain::item& item ) -> void
    {
        const auto delete_item = fmt::format(
            "DELETE FROM items WHERE name = \"{}\";", item.get_name() );
        db_.run_query( delete_item );
    }

    auto find_by_name( std::string item_id ) -> types::record
    {
        const auto find_query =
            fmt::format( "SELECT * FROM items WHERE name = \"{}\";", item_id );
        auto result = db_.run_query( find_query );
        if ( result.has_value() )
        {
            return *result->begin();
        }
        return types::record {};
    }

    [[nodiscard]] auto record_to_armor( types::record record )
        -> domain::armor::pointer
    {
        auto get_column_value = [ &record ]( const auto& col ) {
            return std::find_if(
                       std::begin( record ),
                       std::end( record ),
                       [ col ]( const auto& p ) { return p.first == col; } )
                ->second;
        };

        auto name = get_column_value( "name" );
        auto value = get_column_value( "value" );
        auto level = get_column_value( "level" );
        auto defense = get_column_value( "defense" );

        return std::make_shared<domain::armor>( *name,
                                                double( std::stoi( *value ) ) /
                                                    domain::money::SCALE(),
                                                std::stoi( *level ),
                                                std::stoi( *defense ) );
    }

    [[nodiscard]] auto record_to_weapon( types::record record )
        -> domain::weapon::pointer
    {
        auto get_column_value = [ &record ]( const auto& col ) {
            return std::find_if(
                       std::begin( record ),
                       std::end( record ),
                       [ col ]( const auto& p ) { return p.first == col; } )
                ->second;
        };

        auto name = get_column_value( "name" );
        auto value = get_column_value( "value" );
        auto level = get_column_value( "level" );
        auto attack = get_column_value( "attack" );

        return std::make_shared<domain::weapon>( *name,
                                                 double( std::stoi( *value ) ) /
                                                     domain::money::SCALE(),
                                                 std::stoi( *level ),
                                                 std::stoi( *attack ) );
    }

    [[nodiscard]] auto record_to_potion( types::record record )
        -> domain::health_potion::pointer
    {
        auto get_column_value = [ &record ]( const auto& col ) {
            return std::find_if(
                       std::begin( record ),
                       std::end( record ),
                       [ col ]( const auto& p ) { return p.first == col; } )
                ->second;
        };

        auto name = get_column_value( "name" );
        auto value = get_column_value( "value" );
        auto level = get_column_value( "level" );
        auto power = get_column_value( "power" );

        return std::make_shared<domain::health_potion>(
            *name,
            double( std::stoi( *value ) ) / domain::money::SCALE(),
            std::stoi( *level ),
            std::stoi( *power ) );
    }

    [[nodiscard]] auto get_item_on_level( int lvl ) -> domain::item::pointer
    {
        const auto& query =
            fmt::format( "SELECT * FROM items WHERE level = {};", lvl );
        auto result = db_.run_query( query );

        if ( result.has_value() )
        {

            static auto dev = std::random_device {};
            static auto rng = std::mt19937 { dev() };
            static auto dist = std::uniform_int_distribution<> {
                0, static_cast<int>( result.value().size() ) - 1
            };
            auto it = std::begin( result.value() );
            std::advance( it, dist( rng ) );

            auto record = *it;

            auto get_column_value = [ &record ]( const auto& col ) {
                return std::find_if(
                           std::begin( record ),
                           std::end( record ),
                           [ col ]( const auto& p ) { return p.first == col; } )
                    ->second;
            };

            auto name = get_column_value( "name" );
            auto value = get_column_value( "value" );
            auto level = get_column_value( "level" );
            auto defense = get_column_value( "defense" );
            auto attack = get_column_value( "attack" );
            auto power = get_column_value( "power" );

            if ( defense && std::stoi( *defense ) )
            {
                return std::make_shared<domain::armor>(
                    *name,
                    double( std::stoi( *value ) ) / domain::money::SCALE(),
                    std::stoi( *level ),
                    std::stoi( *defense ) );
            }

            if ( attack && std::stoi( *attack ) )
            {
                return std::make_shared<domain::weapon>(
                    *name,
                    double( std::stoi( *value ) ) / domain::money::SCALE(),
                    std::stoi( *level ),
                    std::stoi( *attack ) );
            }

            if ( power && std::stoi( *power ) )
            {
                return std::make_shared<domain::health_potion>(
                    *name,
                    double( std::stoi( *value ) ) / domain::money::SCALE(),
                    std::stoi( *level ),
                    std::stoi( *power ) );
            }
        }
        return get_item_on_level( lvl - 1 );
    }

private:
    DB& db_;
};

} // namespace asciinem::server::db

#endif // ASCIINEM_SERVER_ITEM_MAPPER_H
