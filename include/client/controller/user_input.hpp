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
    QUIT,
    INVALID
};

auto cast_to_user_input( int c ) -> user_input
{
    switch ( c )
    {
    case 'w':
        return user_input::UP;
    case 's':
        return user_input::DOWN;
    case 'a':
        return user_input::LEFT;
    case 'd':
        return user_input::RIGHT;
    case 'q':
        return user_input::QUIT;
    default:
        return user_input::INVALID;
    }
}

} // namespace asciinem::client::view::console

#endif // ASCIINEM_CLIENT_USER_INPUT_H
