#ifndef ASCIINEM_SEVER_PLAYER_H
#define ASCIINEM_SEVER_PLAYER_H

#include "armor.hpp"
#include "entity.hpp"
#include "item.hpp"
#include "weapon.hpp"

#include <optional>
#include <set>

namespace asciinem::server::domain
{

class player : public entity
{
public:
    player( const std::string& name,
            const std::pair<int, int>& position,
            int health,
            std::set<item::pointer> backpack,
            unsigned int backpack_capacity );

    void add_to_backpack( const item::pointer& item );
    void take_from_backpack( const item::pointer& item );
    auto has( const item& item ) -> bool;

    void use( const weapon::pointer& weapon );
    void use( const armor::pointer& armor );

    auto get_attack() -> int;
    auto get_defense() -> int;

private:
    int coins = 0; // todo change to money pattern
    std::set<item::pointer> backpack_;
    unsigned int backpack_capacity_;
    std::optional<weapon::pointer> weapon_;
    std::optional<armor::pointer> armor_;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SEVER_PLAYER_H
