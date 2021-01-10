#ifndef ASCIINEM_SERVER_SERVICE_HPP
#define ASCIINEM_SERVER_SERVICE_HPP

#include "server/domain/game_manager.hpp"
#include "server/domain/game_state.hpp"

namespace asciinem::server::service
{

class game_service
{
public:
    explicit game_service( domain::game_manager& game );

    [[nodiscard]] auto get_state() const -> domain::game_state;
    void login( const std::string& login );
    void logout( const std::string& login );
    void move_up( const std::string& login );
    void move_down( const std::string& login );
    void move_left( const std::string& login );
    void move_right( const std::string& login );
    void fight( const std::string& login );
    void use( const std::string& login, int ind );
    void tick();

private:
    domain::game_manager& game_;
};

} // namespace asciinem::server::service

#endif // ASCIINEM_SERVER_SERVICE_HPP
