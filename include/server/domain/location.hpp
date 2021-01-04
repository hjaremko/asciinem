#ifndef ASCIINEM_SERVER_LOCATION_H
#define ASCIINEM_SERVER_LOCATION_H

#include <string>
#include <vector>

namespace asciinem::server::domain
{

class location
{
public:
    location( const std::string& map_filename,
              const std::string& collision_map_filename );

    [[nodiscard]] auto get_map() -> std::vector<std::string>;
    [[nodiscard]] auto get_collision_map() -> std::vector<std::vector<bool>>&;

private:
    std::vector<std::string> map_;
    std::vector<std::vector<bool>> collision_map_;
};

} // namespace asciinem::server::domain
#endif // ASCIINEM_LOCATION_H
