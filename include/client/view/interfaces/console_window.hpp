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

template <class Curses>
class ncurses_window : public console_window
{
public:
    ncurses_window() = default;

    explicit ncurses_window( typename Curses::raw_window_ptr win )
        : window_( win ) {};

    ncurses_window( int y, int x, int height, int width )
        : window_( Curses::make_window( y, x, height, width ) )
    {
    }

    ~ncurses_window() override
    {
        Curses::destroy_window( window_ );
    }

    void clear() const override
    {
        Curses::clear( window_ );
    }

    void refresh() const override
    {
        Curses::refresh( window_ );
    }

    void draw_border() override
    {
        Curses::draw_border( window_ );
    }

    [[nodiscard]] auto get_center() const -> std::pair<int, int> override
    {
        return Curses::get_center( window_ );
    }

    [[nodiscard]] auto max_height() const -> int override
    {
        return Curses::max_height( window_ );
    }

    [[nodiscard]] auto max_width() const -> int override
    {
        return Curses::max_width( window_ );
    }

    void print( int y, int x, const std::string& format ) override
    {
        Curses::print( window_, y, x, format );
    }

    void set_bold() override
    {
        Curses::set_bold( window_ );
    }

    void set_red() override
    {
        Curses::set_red( window_ );
    }

    void set_yellow() override
    {
        Curses::set_yellow( window_ );
    }

    void set_blue() override
    {
        Curses::set_blue( window_ );
    }

    void set_green() override
    {
        Curses::set_green( window_ );
    }

    void set_normal() override
    {
        Curses::set_normal( window_ );
    }

    void move( int y, int x ) override
    {
        Curses::move( window_, y, x );
    }

private:
    typename Curses::raw_window_ptr window_;
};

template <class Curses>
class ncurses_main_window : public ncurses_window<Curses>
{
public:
    ncurses_main_window()
        : ncurses_window<Curses>(
              ( Curses::initialize(), Curses::standard_screen() ) )
    {
    }

    ~ncurses_main_window() override
    {
        Curses::end();
    }
};

} // namespace asciinem::client::view

#endif // ASCIINEM_CLIENT_VIEW_WINDOW_HPP
