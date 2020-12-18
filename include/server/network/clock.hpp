#ifndef ASCIINEM_CLOCK_HPP
#define ASCIINEM_CLOCK_HPP

#include "network/interfaces/subject.hpp"

#include <thread>

namespace asciinem::server::network
{

template <int Interval>
class clock : public subject
{
public:
    clock() : thread_( &clock::running_function, this )
    {
    }

    ~clock() override
    {
        running_.store( false );
        thread_.join();
    }

    clock( const clock& ) = delete;
    clock( clock&& ) noexcept = delete;
    auto operator=( const clock& ) -> clock& = delete;
    auto operator=( clock&& ) noexcept -> clock& = delete;

    // not sure if needed
    auto current_tick() -> int
    {
        return tick_.load();
    }

    void notify() override
    {
        tick_.fetch_add( 1 ); // todo: what if overflows
        subject::notify();
    }

    void stop()
    {
        running_.store( false );
    }

private:
    void running_function()
    {
        spdlog::info( "Starting server clock..." );

        while ( running_.load() )
        {
            notify();
            std::this_thread::sleep_for(
                std::chrono::milliseconds( Interval ) );
        }

        spdlog::info( "Stopping server clock..." );
    }

    std::atomic<long long> tick_ {};
    std::atomic_bool running_ { true };
    std::thread thread_;
};

template <int Interval>
auto make_clock()
{
    return std::make_shared<clock<Interval>>();
}

} // namespace asciinem::server::network

#endif // ASCIINEM_CLOCK_HPP
