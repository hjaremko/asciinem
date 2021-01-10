#include "server/domain/collision_checker.hpp"

using namespace asciinem::server::domain;

auto collision_checker::check_collision( const player::position_type& f_pos,
                                         int f_length,
                                         const player::position_type& s_pos,
                                         int s_length ) -> bool
{

    auto f_s = std::set<entity::position_type> {};

    for ( auto f = 0; f < f_length; f++ )
    {
        f_s.insert( { f_pos.first + f, f_pos.second } );
    }

    for ( auto s = 0; s < s_length; s++ )
    {
        for ( const auto& pos : f_s )
        {
            if ( pos == std::make_pair( s_pos.first + s, s_pos.second ) )
            {
                return true;
            }
        }
    }

    return false;
}

auto collision_checker::check_collision( const player::position_type& p_pos,
                                         int p_length,
                                         const location& location ) -> bool
{

    for ( auto f = 0; f < p_length; f++ )
    {
        if ( location.get_collision_map()
                 .at( static_cast<unsigned long>( p_pos.second ) )
                 .at( static_cast<unsigned long>( p_pos.first ) +
                      static_cast<unsigned long>( f ) ) )
        {
            return true;
        }
    }

    return false;
}
