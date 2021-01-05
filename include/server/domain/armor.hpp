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
    void serialize( Archive& ar )
    {
        ar( cereal::virtual_base_class<item>( this ), defense_ );
    }

private:
    int defense_ { 0 };
};

} // namespace asciinem::server::domain

CEREAL_REGISTER_TYPE( asciinem::server::domain::armor )

#endif // ASCIINEM_SERVER_ARMOR_H
