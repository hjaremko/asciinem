#ifndef ASCIINEM_SERVER_GAME_MANAGER_HPP
#define ASCIINEM_SERVER_GAME_MANAGER_HPP

#include "entity.hpp"
#include "game_state.hpp"
#include "server/db/database.hpp"
#include "server/db/mappers/player_mapper.hpp"
#include "server/db/sqlite_connection.hpp"

#include <string>

namespace asciinem::server::domain
{

class game_manager
{
public:
    game_manager();

    [[nodiscard]] auto get_state() const -> game_state;
    void move_player( const std::string& login,
                      const entity::position_type& offset );
    void fight( const std::string& login );
    void use( const std::string& login, int ind );
    void add_player( const std::string& login );
    void remove_player( const std::string& login );
    void remove_dead_monsters();
    void tick();

private:
    void move_monsters();

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
