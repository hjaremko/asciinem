#include "server/domain/collision_checker.hpp"

#include <spdlog/spdlog.h>

using namespace asciinem::server::domain;

auto collision_checker::check_collision(
    const player::position_type& f_pos,
    int f_length,
    const player::position_type& s_pos,
    int s_length
) -> bool
{

    auto f_s = std::set<entity::position_type>{};

    for (auto f = 0; f < f_length; f++)
    {
        f_s.insert({f_pos.first + f, f_pos.second});
    }

    for (auto s = 0; s < s_length; s++)
    {
        for (const auto& pos : f_s)
        {
            if (pos == std::make_pair(s_pos.first + s, s_pos.second))
            {
                return true;
            }
        }
    }

    return false;
}

auto collision_checker::check_collision(
    const player::position_type& p_pos,
    int p_length,
    const location& location
) -> bool
{
    const auto [x, y] = p_pos;
    const auto& collision_map = location.get_collision_map();

    for (auto f = 0; f < p_length; f++)
    {
        auto is_out_of_bounds = [collision_map, f](int i, int j)
        {
            const auto map_height = static_cast<int>(collision_map.size());
            if (j < 0 || j >= map_height || i + f < 0)
            {
                return true;
            }

            const auto map_width =
                static_cast<int>(collision_map.at(static_cast<size_t>(j)).size()
                );

            return i + f >= map_width;
        };

        if (is_out_of_bounds(x, y))
        {
            // todo: add player context?
            spdlog::debug("Player out of map bounds: {}, {}", x, y);
            return false;
        }

        int i = y;
        int j = x + f;
        if (collision_map.at(i).at(j))
        {
            return true;
        }
    }

    return false;
}
