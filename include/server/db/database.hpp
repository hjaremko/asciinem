#ifndef ASCIINEM_DATABASE_HPP
#define ASCIINEM_DATABASE_HPP

#include <string>
#include <utility>

namespace asciinem::server::db
{

// bridge
template <class DbImplementation>
class database
{
public:
    explicit database( std::string db_name ) : impl_( std::move( db_name ) )
    {
    }

    auto run_query( const std::string& query ) const
    {
        return impl_.run_query( query );
    }

private:
    const DbImplementation impl_;
};

} // namespace asciinem::server::db

#endif // ASCIINEM_DATABASE_HPP
