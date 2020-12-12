#ifndef ASCIINEM_OBSERVER_HPP
#define ASCIINEM_OBSERVER_HPP

#include <memory>
#include <string>

namespace asciinem::server::network
{

class observer
{
public:
    using pointer = std::shared_ptr<observer>;

    observer( const observer& ) = default;
    observer( observer&& ) noexcept = default;
    auto operator=( const observer& ) -> observer& = default;
    auto operator=( observer&& ) noexcept -> observer& = default;
    virtual ~observer() = default;

    virtual void update() = 0;
    virtual auto name() -> std::string = 0;

protected:
    observer() = default;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_OBSERVER_HPP
