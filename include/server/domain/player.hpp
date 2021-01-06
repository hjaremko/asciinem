#ifndef ASCIINEM_SEVER_PLAYER_H
#define ASCIINEM_SEVER_PLAYER_H

#include "armor.hpp"
#include "entity.hpp"
#include "health_potion.hpp"
#include "item.hpp"
#include "util/money.hpp"
#include "weapon.hpp"

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/set.hpp>
#include <optional>
#include <set>

namespace asciinem::server::domain
{

class player : public entity
{
public:
    using pointer = std::shared_ptr<player>;

    explicit player( const std::string& name );
    player() = default;
    player( const std::string& name,
            const entity::position_type& position,
            int level,
            int exp,
            double amount,
            std::set<item::pointer> backpack,
            unsigned int backpack_capacity,
            weapon::pointer weapon = nullptr,
            armor::pointer armor = nullptr );
    player( const std::string& name,
            const entity::position_type& position,
            int health,
            int level,
            int exp,
            double amount,
            std::set<item::pointer> backpack,
            unsigned int backpack_capacity,
            weapon::pointer weapon = nullptr,
            armor::pointer armor = nullptr );

    void level_up() override;
    void reset();

    auto operator==( const player& rhs ) const -> bool;
    auto operator!=( const player& rhs ) const -> bool;

    void add_to_backpack( const item::pointer& item );
    void take_from_backpack( const item::pointer& item );
    auto has( const item& item ) -> bool;

    [[nodiscard]] auto get_attack() const -> int override;
    [[nodiscard]] auto get_defense() const -> int override;
    [[nodiscard]] auto get_exp() const -> int;
    [[nodiscard]] auto get_money() const -> money;
    [[nodiscard]] auto get_backpack_capacity() const -> unsigned int;
    [[nodiscard]] auto get_weapon() const -> weapon::pointer;
    [[nodiscard]] auto get_armor() const -> armor::pointer;
    [[nodiscard]] auto get_backpack() const -> std::set<item::pointer>;
    void set_weapon( const weapon::pointer& weapon );

    void gain_health( int health );
    auto gain_exp( int exp ) -> bool;
    void set_money( double amount );
    void set_backpack_capacity( unsigned int );
    void set_armor( const armor::pointer& armor );

    template <class Archive>
    void serialize( Archive& ar )
    {
        ar( cereal::virtual_base_class<entity>( this ),
            exp_,
            money_,
            backpack_,
            backpack_capacity_,
            weapon_,
            armor_ );
    }

private:
    int exp_ { 0 };
    money money_;
    std::set<item::pointer> backpack_;
    unsigned int backpack_capacity_ { 0 };
    weapon::pointer weapon_;
    armor::pointer armor_;
};

} // namespace asciinem::server::domain

CEREAL_REGISTER_TYPE( asciinem::server::domain::player )

#endif // ASCIINEM_SEVER_PLAYER_H