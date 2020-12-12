#ifndef ASCIINEM_DATABASE_HPP
#define ASCIINEM_DATABASE_HPP

#include <string>
#include <utility>

namespace asciinem::server::db
{

// todo:
// template <class DatabaseImplementation>
// class player_mapper
//{
// public:
//    auto add_player( const player& ) -> bool
//    {
//        impl_.run_query(player -> sql query);
//    }
//
//    auto remove_player( const player& ) -> bool;
//    auto find_player( const player::id_type& ) -> bool;
//
// private:
//    DatabaseImplementation impl_;
//};

template <class DbImplementation>
class database // : public player_mapper<DbImplementation>,
               // public npc_mapper<DbImplementation>, ...
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
