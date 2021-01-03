#ifndef ASCIINEM_SERVER_GAME_MANAGER_HPP
#define ASCIINEM_SERVER_GAME_MANAGER_HPP

#include "game_state.hpp"
#include "player.hpp"

namespace asciinem::server::domain
{

class game_manager
{
public:
    [[nodiscard]] auto get_state() const -> game_state
    {
        return current_state_;
    }

    void move_player( const std::string& login,
                      const entity::position_type& offset )
    {
        auto player = find_entity( login );
        auto pos = player->get_position();

        pos.first += offset.first;
        pos.second += offset.second;

        player->set_position( pos );
    }

    void add_player( const player::pointer& player )
    {
        current_state_.get_entities().insert( player );
    }

    void remove_player( const entity::pointer& player )
    {
        current_state_.get_entities().erase( player );
    }

    auto find_entity( const std::string& name ) -> entity::pointer
    {
        auto entities = current_state_.get_entities();
        auto entity_it = std::find_if(
            std::begin( entities ),
            std::end( entities ),
            [ name ]( const auto& e ) { return e->get_name() == name; } );

        if ( entity_it == std::end( entities ) )
        {
            throw std::runtime_error( "No such entity: " + name );
        }

        return *entity_it;
    }

private:
    game_state current_state_;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_GAME_MANAGER_HPP
