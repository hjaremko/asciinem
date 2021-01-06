#ifndef ASCIINEM_SERVER_LOCATION_H
#define ASCIINEM_SERVER_LOCATION_H

#include <cereal/types/vector.hpp>
#include <string>
#include <vector>

namespace asciinem::server::domain
{

class location
{
public:
    location( const std::string& map_filename,
              const std::string& collision_map_filename );

    [[nodiscard]] auto get_map() const -> std::vector<std::string>;
    [[nodiscard]] auto get_folded_map() const -> std::string;
    [[nodiscard]] auto get_collision_map() const
        -> std::vector<std::vector<bool>>;

    template <class Archive>
    void serialize( Archive& ar )
    {
        ar( map_ );
    }

private:
    std::vector<std::string> map_;
    std::vector<std::vector<bool>> collision_map_;
};

} // namespace asciinem::server::domain
#endif // ASCIINEM_LOCATION_H
