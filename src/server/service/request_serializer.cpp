#include "server/service/request_serializer.hpp"

#include <sstream>

namespace asciinem::server::service
{

request_serializer::request_serializer( game_service& game ) : game_( game )
{
}

auto request_serializer::deserialize( const network::types::msg& msg )
    -> std::optional<request>
{
    auto split_msg = [ &msg ]() -> std::pair<std::string, std::string> {
        auto ss = std::stringstream( msg );
        auto login = std::string();
        auto comm = std::string();
        ss >> login >> comm;
        comm.pop_back();

        return { login, comm };
    };

    auto [ login, command ] = split_msg();

    spdlog::info( "Received request {} from {}", command, login );

    if ( command == "login;" )
    {
        return request { [ this, login = login ]() { game_.login( login ); } };
    }

    if ( command == "logout;" )
    {
        return request { [ this, login = login ]() { game_.logout( login ); } };
    }

    if ( command == "move_up;" )
    {
        return request { [ this, login = login ]() {
            game_.move_up( login );
        } };
    }

    if ( command == "move_down;" )
    {
        return request { [ this, login = login ]() {
            game_.move_down( login );
        } };
    }

    if ( command == "move_left;" )
    {
        return request { [ this, login = login ]() {
            game_.move_left( login );
        } };
    }

    if ( command == "move_right;" )
    {
        return request { [ this, login = login ]() {
            game_.move_right( login );
        } };
    }

    if ( command == "fight;" )
    {
        return request { [ this, login = login ]() { game_.fight( login ); } };
    }

    if ( command.find( "use", 0 ) == 0 )
    {
        int ind = command[ 3 ] - '0';
        return request { [ this, login = login, ind = ind ]() {
            game_.use( login, ind );
        } };
    }

    spdlog::warn( "Invalid request `{}` from {}", command, login );
    return std::nullopt;
}

} // namespace asciinem::server::service