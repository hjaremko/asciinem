#ifndef ASCIINEM_SERVER_POTION_H
#define ASCIINEM_SERVER_POTION_H

#include "item.hpp"
namespace asciinem::server::domain
{

class health_potion : public item
{
public:
    using pointer = std::shared_ptr<health_potion>;

    health_potion() = default;
    explicit health_potion(
        int id, std::string name, double value, int level, int power );

    [[nodiscard]] auto get_power() const -> int;
    void set_power( int power );

    template <class Archive>
    void save( Archive& ar ) const
    {
        ar( id_, name_, value_, level_, power_ );
    }

    template <class Archive>
    void load( Archive& ar )
    {
        ar( id_, name_, value_, level_, power_ );
    }

private:
    int power_ { 0 };
};

} // namespace asciinem::server::domain
#endif // ASCIINEM_SERVER_POTION_H
