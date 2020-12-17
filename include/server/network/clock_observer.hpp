#ifndef ASCIINEM_CLOCK_OBSERVER_HPP
#define ASCIINEM_CLOCK_OBSERVER_HPP

#include "interfaces/observer.hpp"

#include <functional>

namespace asciinem::server::network
{

class clock_observer : public network::observer
{
public:
    using pointer = std::shared_ptr<clock_observer>;

    template <class F>
    clock_observer( std::string name, F fun )
        : name_( std::move( name ) ), fun_( std::move( fun ) )
    {
    }

    void update() override
    {
        fun_();
    }

    auto name() -> std::string override
    {
        return name_;
    }

private:
    std::string name_;
    std::function<void()> fun_;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_CLOCK_OBSERVER_HPP
