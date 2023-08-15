#ifndef ASCIINEM_SERVER_BACKPACK_MAPPER_HPP
#define ASCIINEM_SERVER_BACKPACK_MAPPER_HPP

#include "item_mapper.hpp"

#include <fmt/format.h>
#include <set>

using namespace std::string_literals;

namespace asciinem::server::db
{

template <typename DB>
class backpack_mapper
{
public:
    explicit backpack_mapper(DB& db)
        : db_(db)
    {
        const auto create_query =
            "CREATE TABLE IF NOT EXISTS backpacks("
            "id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,"
            "player_login VARCHAR(50) NOT NULL,"
            "item_name VARCHAR(50) NOT NULL,"
            "FOREIGN KEY (player_login)"
            "   REFERENCES players (login)"
            "   ON DELETE CASCADE"
            "   ON UPDATE NO ACTION,"
            "FOREIGN KEY (item_name)"
            "   REFERENCES items (name)"
            "   ON DELETE CASCADE"
            "   ON UPDATE NO ACTION);"s;
        db_.run_query(create_query);
    };

    void insert_player_item(const std::string& login, const std::string& item)
    {
        const auto insert_pair_query = fmt::format(
            "INSERT INTO backpacks (player_login, item_name) VALUES "
            "(\"{}\", \"{}\");",
            login,
            item
        );
        db_.run_query(insert_pair_query);
    }

    void insert_player_backpack(
        const std::string& login,
        const std::set<domain::item::pointer>& backpack
    )
    {
        for (const auto& i : backpack)
        {
            insert_player_item(login, i->get_name());
        }
    }

    auto get_backpack_for_player(std::string login)
        -> std::set<domain::item::pointer>
    {
        const auto find_query = fmt::format(
            "SELECT * FROM backpacks WHERE player_login = \"{}\"",
            login
        );
        auto result = db_.run_query(find_query);

        auto im = item_mapper(db_);
        std::set<domain::item::pointer> backpack = {};

        if (!result.has_value())
        {
            return backpack;
        }

        for (const auto& r : *result)
        {
            auto get_column = [](const auto& record, const auto& col)
            {
                return std::find_if(
                    std::begin(record),
                    std::end(record),
                    [col](const auto& p)
                    {
                        return p.first == col;
                    }
                );
            };

            auto ind = get_column(r, "item_name");
            if (ind != std::end(r))
            {
                const auto& record = im.find_by_name(*ind->second);
                auto attack = get_column(record, "attack")->second;
                auto defense = get_column(record, "defense")->second;
                auto power = get_column(record, "power")->second;

                if (attack && std::stoi(*attack))
                {
                    spdlog::warn("Getting weapon " + *ind->second);
                    backpack.insert(im.record_to_weapon(record));
                }
                else if (defense && std::stoi(*defense))
                {
                    spdlog::warn("Getting armor " + *ind->second);
                    backpack.insert(im.record_to_armor(record));
                }
                else if (power && std::stoi(*power))
                {
                    spdlog::warn("Getting potion " + *ind->second);
                    backpack.insert(im.record_to_potion(record));
                }
            }
        }
        return backpack;
    }

    void remove_all_for_player(const std::string& login)
    {
        const auto delete_player_query = fmt::format(
            "DELETE FROM backpacks WHERE player_login = \"{}\";",
            login
        );
        db_.run_query(delete_player_query);
    }

private:
    DB& db_;
};

} // namespace asciinem::server::db

#endif // ASCIINEM_SERVER_BACKPACK_MAPPER_HPP
