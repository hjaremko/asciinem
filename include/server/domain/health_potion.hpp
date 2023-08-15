#ifndef ASCIINEM_SERVER_POTION_H
#define ASCIINEM_SERVER_POTION_H

#include "item.hpp"
namespace asciinem::server::domain
{

class health_potion : public item,
                      public std::enable_shared_from_this<health_potion>
{
public:
    using pointer = std::shared_ptr<health_potion>;

    health_potion() = default;
    explicit health_potion(
        std::string name,
        double value,
        int level,
        int power
    );

    [[nodiscard]] auto get_power() const -> int;
    void set_power(int power);

    void use(player& player) override;

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(cereal::virtual_base_class<item>(this), power_);
    }

private:
    int power_{0};
};

} // namespace asciinem::server::domain

CEREAL_REGISTER_TYPE(asciinem::server::domain::health_potion)

#endif // ASCIINEM_SERVER_POTION_H
