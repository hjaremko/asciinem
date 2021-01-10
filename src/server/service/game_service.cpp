#include "server/service/game_service.hpp"

namespace asciinem::server::service
{

game_service::game_service( domain::game_manager& game ) : game_( game )
{
}

auto game_service::get_state() const -> domain::game_state
{
    return game_.get_state();
}

void game_service::login( const std::string& login )
{
    game_.add_player( login );
}

void game_service::logout( const std::string& login )
{
    game_.remove_player( login );
}

void game_service::move_up( const std::string& login )
{
    game_.move_player( login, { 0, -1 } );
}

void game_service::move_down( const std::string& login )
{
    game_.move_player( login, { 0, 1 } );
}

void game_service::move_left( const std::string& login )
{
    game_.move_player( login, { -1, 0 } );
}

void game_service::move_right( const std::string& login )
{
    game_.move_player( login, { 1, 0 } );
}

void game_service::fight( const std::string& login )
{
    spdlog::warn( "Starting fight in game service" );
    game_.fight( login );
    spdlog::warn( "End of fight in game service" );
}

void game_service::use( const std::string& login, int ind )
{
    game_.use( login, ind );
}

void game_service::tick()
{
    game_.tick();
}

} // namespace asciinem::server::service
