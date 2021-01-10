#include "server/domain/game_state.hpp"

#include "server/domain/strategies/still_strategy.hpp"

#include <spdlog/spdlog.h>

namespace asciinem::server::domain
{

auto game_state::get_entities() -> game_state::players_type&
{
    return entities_;
}

auto game_state::get_entities() const -> game_state::players_type
{
    return entities_;
}

auto game_state::get_monsters() -> game_state::monsters_type&
{
    return monsters_;
}

auto game_state::get_monsters() const -> game_state::monsters_type
{
    return monsters_;
}

auto game_state::get_notice() -> std::string&
{
    return notice_;
}

auto game_state::get_notice() const -> std::string
{
    return notice_;
}

void game_state::set_notice( const std::string& notice )
{
    notice_ = notice;
}

void game_state::clear_notice()
{
    notice_ = "";
}

auto game_state::find_player( const std::string& name ) const -> player::pointer
{
    auto find_player = [ name ]( const auto& e ) {
        return e->get_name() == name;
    };

    auto entity_it = std::find_if(
        std::begin( entities_ ), std::end( entities_ ), find_player );

    if ( entity_it == std::end( entities_ ) )
    {
        auto msg = fmt::format( "No such entity: {}", name );
        spdlog::debug( msg );
        return nullptr;
    }

    return *entity_it;
}

void game_state::spawn_monster( entity::position_type where )
{
    monsters_.insert( std::make_shared<monster>( "mob", where, 150, 1 ) );
}

void game_state::spawn_boss( entity::position_type where )
{
    auto boss = std::make_shared<monster>(
        "wonsz rzeczny", where, 200, 5, std::make_shared<still_strategy>() );
    boss->set_shape( "~~~~O<" );
    monsters_.insert( std::move( boss ) );
}

auto game_state::get_map() const -> std::vector<std::string>
{
    return map_.get_map();
}

auto game_state::get_location() const -> location
{
    return map_;
}

} // namespace asciinem::server::domain