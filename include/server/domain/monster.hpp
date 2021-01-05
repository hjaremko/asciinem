#ifndef ASCIINEM_SERVER_MONSTER_H
#define ASCIINEM_SERVER_MONSTER_H

#include "entity.hpp"
#include "strategies/move_strategy.hpp"
#include "strategies/random_move_strategy.hpp"

namespace asciinem::server::domain
{

class monster : public entity
{
public:
    using pointer = std::shared_ptr<monster>;

    monster() = default;
    monster( std::string name,
             position_type position,
             int health,
             int level,
             move_strategy::pointer strategy =
                 std::make_shared<random_move_strategy>() );

    [[nodiscard]] auto get_id() const -> int
    {
        return id_;
    }

    [[nodiscard]] auto get_attack() const -> int override;
    [[nodiscard]] auto get_defense() const -> int override;
    void set_strategy( const move_strategy::pointer& strategy );
    auto move() -> entity::position_type;

    template <class Archive>
    void save( Archive& ar ) const
    {
        ar( cereal::virtual_base_class<entity>( this ) );
    }

    template <class Archive>
    void load( Archive& ar )
    {
        ar( cereal::virtual_base_class<entity>( this ) );
    }

private:
    move_strategy::pointer strategy_;
    static inline auto ids = 0;
    int id_ { ids++ };
};

} // namespace asciinem::server::domain

CEREAL_REGISTER_TYPE( asciinem::server::domain::monster )

#endif // ASCIINEM_SERVER_MONSTER_H
