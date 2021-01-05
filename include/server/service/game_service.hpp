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
        game_.add_player( login );
    }

    void logout( const std::string& login )
    {
        game_.remove_player( login );
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

    void tick()
    {
        game_.tick();
    }

private:
    domain::game_manager& game_;
};

} // namespace asciinem::server::service

#endif // ASCIINEM_SERVER_SERVICE_HPP
