#ifndef ASCIINEM_SERVER_ITEM_H
#define ASCIINEM_SERVER_ITEM_H

#include "util/money.hpp"

#include <cereal/types/polymorphic.hpp>
#include <memory>
#include <string>

namespace asciinem::server::domain
{

class player;

class item
{
public:
    using pointer = std::shared_ptr<item>;

    item() = default;
    item( std::string name, double value, int level );
    item( const item& ) = default;
    item( item&& ) noexcept = delete;
    auto operator=( const item& ) -> item& = default;
    auto operator=( item&& ) noexcept -> item& = delete;
    virtual ~item() = default;

    virtual void use( player& );

    [[nodiscard]] auto get_name() const -> std::string;
    [[nodiscard]] auto get_value() const -> money;
    [[nodiscard]] auto get_level() const -> int;

    void set_value( double value );
    void set_name( const std::string& name );

    friend auto operator<( const item& lhs, const item& rhs ) -> bool;
    friend auto operator==( const item& lhs, const item& rhs ) -> bool;

    friend auto operator!=( const item& lhs, const item& rhs ) -> bool;

    template <class Archive>
    void serialize( Archive& ar )
    {
        ar( name_, value_, level_ );
    }

protected:
    std::string name_;
    money value_;
    int level_ { 0 };
};

} // namespace asciinem::server::domain

CEREAL_REGISTER_TYPE( asciinem::server::domain::item )

#endif // ASCIINEM_SERVER_ITEM_H
