#ifndef ASCIINEM_GAME_VIEW_HPP
#define ASCIINEM_GAME_VIEW_HPP

#include "client/view/window.hpp"

#include <utility>

namespace asciinem::client::view
{

class game_view : public window
{
public:
    using window::window;

    void draw( game_state_cr state, const std::string& login ) override;

private:
    auto find_relative_pos( std::pair<int, int> player_pos,
                            std::pair<int, int> entity_pos )
        -> std::pair<int, int>;
    void print_entity( const asciinem::server::domain::entity::pointer& e,
                       std::pair<int, int> pos,
                       const std::string& look );
};

} // namespace asciinem::client::view

#endif // ASCIINEM_GAME_VIEW_HPP
