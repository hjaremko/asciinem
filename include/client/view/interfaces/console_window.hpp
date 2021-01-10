#ifndef ASCIINEM_CLIENT_VIEW_WINDOW_HPP
#define ASCIINEM_CLIENT_VIEW_WINDOW_HPP

#include "server/domain/game_state.hpp"
#include "server/domain/player.hpp"
#include "server/serializer.hpp"

namespace asciinem::client::view
{

using game_state_cr = const server::domain::game_state&;

class console_window
{
public:
    using pointer = std::unique_ptr<console_window>;

    console_window() = default;
    console_window( const console_window& ) = default;
    console_window( console_window&& ) noexcept = default;
    auto operator=( const console_window& ) -> console_window& = default;
    auto operator=( console_window&& ) noexcept -> console_window& = default;
    virtual ~console_window() = default;

    virtual void clear() const = 0;
    virtual void refresh() const = 0;
    virtual void draw_border() = 0;
    [[nodiscard]] virtual auto get_center() const -> std::pair<int, int> = 0;
    [[nodiscard]] virtual auto max_height() const -> int = 0;
    [[nodiscard]] virtual auto max_width() const -> int = 0;
    virtual void set_bold() = 0;
    virtual void set_red() = 0;
    virtual void set_yellow() = 0;
    virtual void set_blue() = 0;
    virtual void set_green() = 0;
    virtual void set_normal() = 0;
    virtual void move( int, int ) = 0;

    virtual void print( int y, int x, const std::string& format ) = 0;
};

} // namespace asciinem::client::view

#endif // ASCIINEM_CLIENT_VIEW_WINDOW_HPP
