#include "network/asio_listener.hpp"

namespace asciinem::server::network
{

asio_listener::asio_listener( types::port port, const connection_manager::pointer& manager )
    : port_( port ), tcp_server_( port_, io_context_, manager )
{
    start_listening_();
}

asio_listener::~asio_listener()
{
    stop_listening_();
}

void asio_listener::start_listening()
{
    start_listening_();
}

void asio_listener::stop_listening()
{
    stop_listening_();
}

void asio_listener::start_listening_()
{
    if ( thread_.has_value() )
    {
        spdlog::warn( "Listener is already running." );
        return;
    }

    auto listening_thread = [ & ]() {
        spdlog::info( "Starting listening on {}...", port_ );

        try
        {
            io_context_.run();
        }
        catch ( std::exception& e )
        {
            spdlog::error( "Listener error: {}", e.what() );
        }
    };

    thread_ = std::thread( listening_thread );
}

void asio_listener::stop_listening_()
{
    if ( !thread_.has_value() )
    {
        spdlog::warn( "Listener is already stopped." );
        return;
    }

    spdlog::info( "Stopping listening..." );
    io_context_.stop();
    thread_->join();
    thread_ = std::nullopt;
}

} // namespace asciinem::server::network
