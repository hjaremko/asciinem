#ifndef ASCIINEM_NCURSES_WINDOW_HPP
#define ASCIINEM_NCURSES_WINDOW_HPP

namespace asciinem::client::view
{

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

} // namespace asciinem::client::view

#endif // ASCIINEM_NCURSES_WINDOW_HPP
