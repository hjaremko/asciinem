#ifndef ASCIINEM_SERVER_ENTITY_H
#define ASCIINEM_SERVER_ENTITY_H

#include <string>
namespace asciinem::server::domain
{
class entity
{
public:
    void die();

    [[nodiscard]] auto get_name() const -> const std::string&;
    [[nodiscard]] auto get_position() const -> const std::pair<int, int>&;
    [[nodiscard]] auto get_health() const -> int;
    [[nodiscard]] auto get_level() const -> int;

    void set_name( const std::string& name );
    void set_position( const std::pair<int, int>& position );
    void set_health( int health );

    void level_up();

protected:
    entity( std::string name,
            std::pair<int, int> position,
            int health,
            int level );

private:
    std::string name_;
    std::pair<int, int> position_;
    int health_;
    int level_;
};
} // namespace asciinem::server::domain

#endif // ASCIINEM_SERVER_ENTITY_H
