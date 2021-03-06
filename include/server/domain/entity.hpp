#ifndef ASCIINEM_SERVER_ENTITY_H
#define ASCIINEM_SERVER_ENTITY_H

#include <cereal/types/polymorphic.hpp>
#include <memory>
#include <string>

namespace asciinem::server::domain
{
class entity
{
public:
    using pointer = std::shared_ptr<entity>;
    using position_type = std::pair<int, int>;

    entity() = default;
    virtual ~entity() = default;

    [[nodiscard]] virtual auto get_attack() const -> int = 0;
    [[nodiscard]] virtual auto get_defense() const -> int = 0;

    [[nodiscard]] auto get_name() const -> std::string;
    [[nodiscard]] auto get_position() const -> position_type;
    [[nodiscard]] auto get_health() const -> int;
    [[nodiscard]] auto get_max_health() const -> int;
    [[nodiscard]] auto get_level() const -> int;

    void set_name( const std::string& name );
    void set_position( const position_type& position );
    void set_health( int health );
    void set_shape( const std::string& shape );

    [[nodiscard]] auto is_dead() const -> bool;
    virtual void level_up();
    void get_hurt( int damage );
    [[nodiscard]] auto get_shape() const -> const std::string&;

    template <class Archive>
    void serialize( Archive& ar )
    {
        ar( name_, shape_, position_, health_, level_ );
    }

    auto operator==( const entity& rhs ) const -> bool;
    auto operator!=( const entity& rhs ) const -> bool;

protected:
    entity( std::string name,
            std::string shape,
            position_type position,
            int health,
            int level );
    entity( std::string name,
            std::string shape,
            position_type position,
            int level );

    std::string name_;
    std::string shape_;
    position_type position_;
    int health_ { 0 };
    int level_ { 0 };
};
} // namespace asciinem::server::domain

CEREAL_REGISTER_TYPE( asciinem::server::domain::entity )

#endif // ASCIINEM_SERVER_ENTITY_H
