#ifndef ASCIINEM_SERVER_GAME_STATE_HPP
#define ASCIINEM_SERVER_GAME_STATE_HPP

#include <cereal/types/unordered_map.hpp>
#include <cereal/types/utility.hpp>

namespace asciinem::server::domain
{

class game_state
{
public:
    template <class Archive>
    void save( Archive& ar ) const
    {
        ar( players_positions_ );
    }

    template <class Archive>
    void load( Archive& ar )
    {
        ar( players_positions_ );
    }

    // private:
    std::unordered_map<std::string, std::pair<int, int>> players_positions_;
    //    std::pair<int, int> player_pos { 10, 10 };
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_GAME_STATE_HPP
