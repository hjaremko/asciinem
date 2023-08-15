#ifndef ASCIINEM_CLIENT_USER_INPUT_H
#define ASCIINEM_CLIENT_USER_INPUT_H

namespace asciinem::client::view::console
{

enum class user_input
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FIGHT,
    USE0,
    USE1,
    USE2,
    USE3,
    USE4,
    USE5,
    USE6,
    USE7,
    USE8,
    USE9,
    QUIT,
    INVALID
};

auto format_as(user_input i)
{
    return fmt::underlying(i);
}

auto cast_to_user_input(int c) -> user_input
{
    switch (c)
    {
        case 'w':
            return user_input::UP;
        case 's':
            return user_input::DOWN;
        case 'a':
            return user_input::LEFT;
        case 'd':
            return user_input::RIGHT;
        case 'f':
            return user_input::FIGHT;

        case '0':
            return user_input::USE0;
        case '1':
            return user_input::USE1;
        case '2':
            return user_input::USE2;
        case '3':
            return user_input::USE3;
        case '4':
            return user_input::USE4;
        case '5':
            return user_input::USE5;
        case '6':
            return user_input::USE6;
        case '7':
            return user_input::USE7;
        case '8':
            return user_input::USE8;
        case '9':
            return user_input::USE9;

        case 'q':
            return user_input::QUIT;
        default:
            return user_input::INVALID;
    }
}

} // namespace asciinem::client::view::console

#endif // ASCIINEM_CLIENT_USER_INPUT_H
