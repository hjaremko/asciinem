#ifndef ASCIINEM_SERVER_REQUEST_HPP
#define ASCIINEM_SERVER_REQUEST_HPP

namespace asciinem::server::service
{

class request
{
public:
    template <class F>
    explicit request( F f ) : request_( std::move( f ) )
    {
    }

    void operator()()
    {
        spdlog::info( "Invoking request." );
        request_();
    }

private:
    std::function<void()> request_;
};

} // namespace asciinem::server::service

#endif // ASCIINEM_SERVER_REQUEST_HPP
