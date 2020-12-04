#include <ncurses.h>

auto main() -> int
{
    initscr();
    printw( "Hello World !!!" );
    // todo: if macos
    refresh();
    getch();
    endwin();

    return 0;
}