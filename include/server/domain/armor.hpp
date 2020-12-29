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

    explicit armor( std::string name, int value, int level, int defense );

    [[nodiscard]] auto get_defense() const -> int;
    void set_defense( int defense );

private:
    int defense_;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_ARMOR_H
