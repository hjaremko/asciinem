#ifndef ASCIINEM_SERVER_ITEM_H
#define ASCIINEM_SERVER_ITEM_H

#include <memory>
#include <string>

namespace asciinem::server::domain
{

class item
{
public:
    using pointer = std::shared_ptr<item>;

    item( const item& ) = default;
    item( item&& ) noexcept = default;
    auto operator=( const item& ) -> item& = default;
    auto operator=( item&& ) noexcept -> item& = default;
    virtual ~item() = default;

    [[nodiscard]] auto get_name() const -> const std::string&;
    [[nodiscard]] auto get_value() const -> int;
    [[nodiscard]] auto get_level() const -> int;
    void set_value( int value );
    void set_name( const std::string& name );

    friend auto operator<( const item& lhs, const item& rhs ) -> bool;
    friend auto operator==( const item& lhs, const item& rhs ) -> bool;
    friend auto operator!=( const item& lhs, const item& rhs ) -> bool;

protected:
    item( std::string name, int value, int level );

private:
    std::string name_;
    int value_;
    int level_;
};

} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_ITEM_H
