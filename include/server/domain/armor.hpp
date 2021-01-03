#ifndef ASCIINEM_SERVER_ARMOR_H
#define ASCIINEM_SERVER_ARMOR_H

#include "item.hpp"

#include <memory>

namespace asciinem::server::domain
{

class armor : public item
{
public:
    using pointer = std::shared_ptr<armor>;

    armor() = default;
    explicit armor(
        int id, std::string name, double value, int level, int defense );

    [[nodiscard]] auto get_defense() const -> int;
    void set_defense( int defense );

    template <class Archive>
    void save( Archive& ar ) const
    {
        ar( id_, name_, value_, level_, defense_ );
    }

    template <class Archive>
    void load( Archive& ar )
    {
        ar( id_, name_, value_, level_, defense_ );
    }

private:
    int defense_ { 0 };
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_ARMOR_H
