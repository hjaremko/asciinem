#ifndef ASCIINEM_LISTENER_HPP
#define ASCIINEM_LISTENER_HPP

namespace asciinem::server::network
{

class listener
{
public:
    listener() = default;
    listener( const listener& ) = default;
    listener( listener&& ) noexcept = default;
    auto operator=( const listener& ) -> listener& = default;
    auto operator=( listener&& ) noexcept -> listener& = default;

    virtual ~listener() = default;

    virtual void start_listening() = 0;
    virtual void stop_listening() = 0;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_LISTENER_HPP
