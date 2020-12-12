#ifndef ASCIINEM_SUBJECT_HPP
#define ASCIINEM_SUBJECT_HPP

#include "network/interfaces/observer.hpp"

#include <list>
#include <memory>
#include <spdlog/spdlog.h>

namespace asciinem::server::network
{

class subject
{
public:
    using pointer = std::shared_ptr<subject>;

    subject( const subject& ) = default;
    subject( subject&& ) noexcept = default;
    auto operator=( const subject& ) -> subject& = default;
    auto operator=( subject&& ) noexcept -> subject& = default;
    virtual ~subject() = default;

    virtual void attach( const observer::pointer& o )
    {
        std::lock_guard<std::mutex> lock { mutex_ };
        spdlog::debug( "Attaching new observer: {}", o->name() );

        observers_.push_back( o );
    };

    virtual void detach( const observer::pointer& o )
    {
        std::lock_guard<std::mutex> lock { mutex_ };
        spdlog::debug( "Detaching observer: {}", o->name() );

        observers_.remove_if( [ &o ]( auto x ) { return x.get() == o.get(); } );
    };

    virtual void notify()
    {
        std::lock_guard<std::mutex> lock { mutex_ };
        spdlog::debug( "Notifying {} observers", observers_.size() );

        for ( auto& o : observers_ )
        {
            spdlog::debug( "Notifying {}", o->name() );
            o->update();
        }
    }

protected:
    subject() = default;

private:
    std::list<observer::pointer> observers_;
    std::mutex mutex_;
};

} // namespace asciinem::server::network

#endif // ASCIINEM_SUBJECT_HPP
