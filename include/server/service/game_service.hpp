#ifndef ASCIINEM_SERVER_SERVICE_HPP
#define ASCIINEM_SERVER_SERVICE_HPP

#include "server/domain/game_manager.hpp"
#include "server/domain/game_state.hpp"

namespace asciinem::server::service
{

class game_service
{
public:
    explicit game_service( domain::game_manager& game ) : game_( game )
    {
    }

    auto get_state() -> domain::game_state
    {
        return game_.get_state();
    }

    void move_up( const std::string& login )
    {
        game_.current_state_.players_positions_[ login ].first -= 1;
    }

    void move_down( const std::string& login )
    {
        game_.current_state_.players_positions_[ login ].first += 1;
    }

    void move_left( const std::string& login )
    {
        game_.current_state_.players_positions_[ login ].second -= 1;
    }

    void move_right( const std::string& login )
    {
        game_.current_state_.players_positions_[ login ].second += 1;
    }

private:
    domain::game_manager& game_;
};

} // namespace asciinem::server::service

#endif // ASCIINEM_SERVER_SERVICE_HPP
