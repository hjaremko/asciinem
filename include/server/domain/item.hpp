#ifndef ASCIINEM_SERVER_ITEM_H
#define ASCIINEM_SERVER_ITEM_H

#include "util/money.hpp"

#include <memory>
#include <string>

namespace asciinem::server::domain
{

class item
{
public:
    using pointer = std::shared_ptr<item>;

    item() = default;
    item( int id, std::string name, double value, int level );
    item( const item& ) = default;
    item( item&& ) noexcept = delete;
    auto operator=( const item& ) -> item& = default;
    auto operator=( item&& ) noexcept -> item& = delete;
    ~item() = default;

    [[nodiscard]] auto get_name() const -> std::string;
    [[nodiscard]] auto get_value() const -> money;
    [[nodiscard]] auto get_level() const -> int;
    [[nodiscard]] auto get_id() const -> int;

    void set_value( double value );
    void set_name( const std::string& name );

    friend auto operator<( const item& lhs, const item& rhs ) -> bool;
    friend auto operator==( const item& lhs, const item& rhs ) -> bool;

    friend auto operator!=( const item& lhs, const item& rhs ) -> bool;

    template <class Archive>
    void save( Archive& ar ) const
    {
        ar( id_, name_, value_, level_ );
    }

    template <class Archive>
    void load( Archive& ar )
    {
        ar( id_, name_, value_, level_ );
    }

protected:
    int id_ { 0 };
    std::string name_;
    money value_;
    int level_ { 0 };
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_ITEM_H
