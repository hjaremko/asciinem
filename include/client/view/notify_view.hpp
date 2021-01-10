#ifndef ASCIINEM_SERVER_NOTICE_WINDOW_H
#define ASCIINEM_SERVER_NOTICE_WINDOW_H

#include "client/view/window.hpp"

namespace asciinem::client::view
{

class notify_view : public window
{
public:
    using window::window;

    void draw( const server::domain::game_state& state,
               const std::string& login ) override;
};

} // namespace asciinem::client::view

#endif // ASCIINEM_SERVER_NOTICE_WINDOW_H
