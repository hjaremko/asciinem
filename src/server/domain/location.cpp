#include "server/domain/location.hpp"

#include <filesystem>
#include <fstream>
#include <numeric>
#include <spdlog/spdlog.h>

namespace
{

auto does_exist( const std::string& filename ) -> bool
{
    return std::filesystem::exists( filename );
}

} // namespace

using namespace asciinem::server::domain;

location::location( const std::string& map_filename,
                    const std::string& collision_map_filename )
{
    try
    {
        if ( !does_exist( map_filename ) ||
             !does_exist( collision_map_filename ) )
        {
            throw std::runtime_error( "Location map does not exist!" );
        }

        auto read_map = [ map_filename ]() {
            auto map = std::vector<std::string> {};
            auto file = std::ifstream { map_filename };

            for ( auto line = std::string {}; std::getline( file, line ); )
            {
                map.push_back( line );
            }

            return map;
        };

        auto read_collisions = [ collision_map_filename ]() {
            auto collision_map = std::vector<std::vector<bool>> {};
            auto file = std::ifstream { collision_map_filename };

            for ( auto line = std::string {}; std::getline( file, line ); )
            {
                auto bitset = std::vector<bool> {};
                for ( auto& c : line )
                {
                    bitset.push_back( c - '0' );
                }
                collision_map.push_back( bitset );
            }

            return collision_map;
        };

        map_ = read_map();
        collision_map_ = read_collisions();

        spdlog::trace( "Loaded map:\n{}", get_folded_map() );
    }
    catch ( std::exception& e )
    {
        spdlog::error( "Error loading location: {}", e.what() );
    }
}

auto location::get_map() const -> std::vector<std::string>
{
    return map_;
}

auto location::get_folded_map() const -> std::string
{
    return std::accumulate( std::begin( map_ ),
                            std::end( map_ ),
                            std::string {},
                            []( auto acc, const auto& line ) {
                                return std::move( acc ) + line + '\n';
                            } );
}

auto location::get_collision_map() const -> std::vector<std::vector<bool>>
{
    return collision_map_;
}
