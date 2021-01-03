#ifndef ASCIINEM_SERVER_SERVICE_HPP
#define ASCIINEM_SERVER_SERVICE_HPP

#include "server/domain/game_manager.hpp"
#include "server/domain/game_state.hpp"
#include "server/domain/player.hpp"

#include <memory>

namespace asciinem::server::service
{

class game_service
{
public:
    explicit game_service( domain::game_manager& game ) : game_( game )
    {
    }

    [[nodiscard]] auto get_state() const -> domain::game_state
    {
        return game_.get_state();
    }

    void login( const std::string& login )
    {
        // auto player = get_player_from_db( login );
        auto player = std::make_shared<domain::player>(
            login,
            domain::entity::position_type { 5, 5 },
            100,
            1,
            std::set<domain::item::pointer> {},
            2 );

        game_.add_player( player );
    }

    void logout( const std::string& login )
    {
        auto player = game_.find_entity( login );
        game_.remove_player( player );
        // save_to_db( player );
    }

    void move_up( const std::string& login )
    {
        game_.move_player( login, { 0, -1 } );
    }

    void move_down( const std::string& login )
    {
        game_.move_player( login, { 0, 1 } );
    }

    void move_left( const std::string& login )
    {
        game_.move_player( login, { -1, 0 } );
    }

    void move_right( const std::string& login )
    {
        game_.move_player( login, { 1, 0 } );
    }

private:
    domain::game_manager& game_;
};

} // namespace asciinem::server::service

#endif // ASCIINEM_SERVER_SERVICE_HPP
