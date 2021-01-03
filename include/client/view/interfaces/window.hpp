#ifndef ASCIINEM_CLIENT_VIEW_WINDOW_HPP
#define ASCIINEM_CLIENT_VIEW_WINDOW_HPP

#include "server/domain/game_state.hpp"
#include "server/domain/player.hpp"
#include "server/serializer.hpp"

namespace asciinem::client::view
{

using game_state_cr = const server::domain::game_state&;

template <class Console>
class window
{
public:
    using pointer = std::unique_ptr<window<Console>>;

    window( int y, int x, int height, int width )
        : raw_window( y, x, height, width ), height_( height ), width_( width )
    {
    }

    window( const window& ) = default;
    window( window&& ) noexcept = default;
    auto operator=( const window& ) -> window& = default;
    auto operator=( window&& ) noexcept -> window& = default;

    virtual ~window() = default;

    virtual void draw( game_state_cr, const std::string& ) = 0;

    [[nodiscard]] auto height() const -> int
    {
        return height_;
    };

    [[nodiscard]] auto width() const -> int
    {
        return width_;
    };

    void clear() const
    {
        raw_window.clear();
    }

    void refresh() const
    {
        raw_window.refresh();
    }

    void draw_border()
    {
        raw_window.draw_border();
    }

    void draw_line( int y ) const
    {
        raw_window.print( y, 0, "+" + std::string( width() - 1, '-' ) + "+" );
    }

protected:
    typename Console::raw_window raw_window; // NOLINT

private:
    int height_ { 0 };
    int width_ { 0 };
};

} // namespace asciinem::client::view

#endif // ASCIINEM_CLIENT_VIEW_WINDOW_HPP
