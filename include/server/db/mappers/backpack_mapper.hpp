#ifndef ASCIINEM_SERVER_BACKPACK_MAPPER_HPP
#define ASCIINEM_SERVER_BACKPACK_MAPPER_HPP

#include "item_mapper.hpp"

#include <fmt/format.h>
#include <set>

using namespace std::string_literals;

namespace asciinem::server::db
{

template <typename DB>
class backpack_mapper
{
public:
    explicit backpack_mapper( DB& db ) : db_( db )
    {
        const auto create_query =
            "CREATE TABLE IF NOT EXISTS backpacks("
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            "player_login VARCHAR(50) NOT NULL,"
            "item_id INT NOT NULL,"
            "FOREIGN KEY (player_login)"
            "   REFERENCES players (login)"
            "   ON DELETE CASCADE"
            "   ON UPDATE NO ACTION,"
            "FOREIGN KEY (item_id)"
            "   REFERENCES items (item_id)"
            "   ON DELETE CASCADE"
            "   ON UPDATE NO ACTION);"s;
        db_.run_query( create_query );
    };

    void insert_player_item( const std::string& login,
                             const domain::item::pointer& item )
    {
        const auto delete_player_query =
            fmt::format( "INSERT INTO backpacks (player_login, item_id) VALUES "
                         "(\"{}\", {});",
                         login,
                         item->get_id() );
        db_.run_query( delete_player_query );
    }

    void
    insert_player_backpack( const std::string& login,
                            const std::set<domain::item::pointer>& backpack )
    {
        for ( const auto& i : backpack )
        {
            insert_player_item( login, i );
        }
    }

    auto get_backpack_for_player( std::string login )
        -> std::set<domain::item::pointer>
    {
        const auto find_query = fmt::format(
            "SELECT item_id FROM backpacks WHERE player_login = \"{}\"",
            login );
        auto result = db_.run_query( find_query );

        auto im = item_mapper( db_ );
        std::set<domain::item::pointer> backpack = {};

        if (!result.has_value()) {
            return backpack;
        }

        for ( const auto& record : *result )
        {
            auto id = std::find_if(
                std::begin( record ), std::end( record ), []( const auto& p ) {
                    return p.first == "item_id";
                } );
            if ( id != std::end( record ) )
            {
                backpack.insert( im.record_to_item(
                    im.find_by_id( std::stoi( *id->second ) ) ) );
            }
        }
        return backpack;
    }

    void remove_all_for_player( const std::string& login )
    {
        const auto delete_player_query = fmt::format(
            "DELETE FROM backpacks WHERE player_login = \"{}\";", login );
        db_.run_query( delete_player_query );
    }

private:
    DB& db_;
};

} // namespace asciinem::server::db

#endif // ASCIINEM_SERVER_BACKPACK_MAPPER_HPP
