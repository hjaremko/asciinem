#ifndef ASCIINEM_SERVER_COLLISION_CHECKER_H
#define ASCIINEM_SERVER_COLLISION_CHECKER_H

#include "entity.hpp"
#include "location.hpp"
#include "monster.hpp"
#include "player.hpp"
namespace asciinem::server::domain
{

class collision_checker
{
public:
    static auto check_collision( const player::position_type& f_pos,
                                 int f_length,
                                 const player::position_type& s_pos,
                                 int s_length ) -> bool;

    static auto check_collision( const player::position_type& p_pos,
                                 int p_length,
                                 const location& location ) -> bool;
};

} // namespace asciinem::server::domain
#endif // ASCIINEM_SERVER_COLLISION_CHECKER_H
