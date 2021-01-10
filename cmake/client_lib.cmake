set(CLIENT_TARGET_SOURCES
        ${PROJECT_ROOT}/src/client/util.cpp
        ${PROJECT_ROOT}/src/client/network/asio_network_module.cpp
        ${PROJECT_ROOT}/src/client/view/consoles/ncurses.cpp
        ${PROJECT_ROOT}/src/client/view/window.cpp
        ${PROJECT_ROOT}/src/client/view/game_view.cpp
        ${PROJECT_ROOT}/src/client/view/stats_view.cpp
        ${PROJECT_ROOT}/src/client/view/notify_view.cpp
        )

add_library(client_obj STATIC ${CLIENT_TARGET_SOURCES})

target_link_libraries(
        client_obj
        PRIVATE project_options
        project_warnings
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::asio
        CONAN_PKG::cxxopts
        CONAN_PKG::cereal
        CONAN_PKG::ncurses
        server_obj
)
