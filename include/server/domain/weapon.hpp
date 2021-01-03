#ifndef ASCIINEM_SERVER_WEAPON_H
#define ASCIINEM_SERVER_WEAPON_H

#include "item.hpp"

#include <memory>

namespace asciinem::server::domain
{

class weapon : public item
{
public:
    using pointer = std::shared_ptr<weapon>;

    weapon() = default;
    explicit weapon(
        int id, std::string name, double value, int level, int attack );

    [[nodiscard]] auto get_attack() const -> int;
    void set_attack( int attack );

    template <class Archive>
    void save( Archive& ar ) const
    {
        ar( id_, name_, value_, level_, attack_ );
    }

    template <class Archive>
    void load( Archive& ar )
    {
        ar( id_, name_, value_, level_, attack_ );
    }

private:
    int attack_ { 0 };
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_WEAPON_H
