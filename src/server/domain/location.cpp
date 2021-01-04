#include "server/domain/location.hpp"

#include <fstream>
using namespace asciinem::server::domain;

location::location( const std::string& map_filename,
                    const std::string& collision_map_filename )
{
    std::vector<std::string> map;
    std::ifstream mapFileout;
    mapFileout.open( map_filename );
    std::string line;
    while ( std::getline( mapFileout, line ) )
    {
        map.push_back( line );
    }
    map_ = map;
    mapFileout.close();

    std::vector<std::vector<bool>> collision_map;
    mapFileout.open( collision_map_filename );
    while ( std::getline( mapFileout, line ) )
    {
        std::vector<bool> bitset;
        for ( auto& c : line )
        {
            bitset.push_back( c - '0' );
        }
        collision_map.push_back( bitset );
    }
    collision_map_ = collision_map;
    mapFileout.close();
}

auto location::get_map() -> std::vector<std::string>
{
    return map_;
}

auto location::get_collision_map() -> std::vector<std::vector<bool>>&
{
    return collision_map_;
}
