#ifndef ASCIINEM_SERVER_REQUEST_HPP
#define ASCIINEM_SERVER_REQUEST_HPP

namespace asciinem::server::service
{

// command
class request
{
public:
    template <class F>
    explicit request( F f ) : request_( std::move( f ) )
    {
    }

    void operator()()
    {
        spdlog::debug( "Invoking request" );
        request_();
    }

    static auto make_login_request( const network::types::id& login )
        -> network::types::msg
    {
        return login + " login;;";
    }

    static auto make_logout_request( const network::types::id& login )
        -> network::types::msg
    {
        return login + " logout;;";
    }

private:
    std::function<void()> request_;
};

} // namespace asciinem::server::service

#endif // ASCIINEM_SERVER_REQUEST_HPP
