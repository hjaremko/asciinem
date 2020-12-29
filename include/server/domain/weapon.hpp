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

    explicit weapon( std::string name, int value, int level, int attack );

    [[nodiscard]] auto get_attack() const -> int;
    void set_attack( int attack );

private:
    int attack_;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_WEAPON_H
