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
    using pointer = std::shared_ptr<player>;

    player( const std::string& name,
            const std::pair<int, int>& position,
            int health,
            int level,
            std::set<item::pointer> backpack,
            unsigned int backpack_capacity,
            weapon::pointer weapon = nullptr,
            armor::pointer armor = nullptr );

    auto operator==( const player& rhs ) const -> bool;
    auto operator!=( const player& rhs ) const -> bool;

    void add_to_backpack( const item::pointer& item );
    void take_from_backpack( const item::pointer& item );
    auto has( const item& item ) -> bool;

    void use( const weapon::pointer& weapon );
    void use( const armor::pointer& armor );

    auto get_attack() -> int;
    auto get_defense() -> int;
    [[nodiscard]] auto get_backpack_capacity() const -> unsigned int;
    [[nodiscard]] auto get_weapon() const -> weapon::pointer;
    [[nodiscard]] auto get_armor() const -> armor::pointer;
    [[nodiscard]] auto get_backpack() const -> const std::set<item::pointer>&;

    void set_backpack_capacity( unsigned int backpackCapacity );

private:
    int coins = 0; // todo change to money pattern
    std::set<item::pointer> backpack_;
    unsigned int backpack_capacity_;
    weapon::pointer weapon_;
    armor::pointer armor_;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SEVER_PLAYER_H
