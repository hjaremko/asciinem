set(CLIENT_TARGET_SOURCES
        ${PROJECT_ROOT}/src/client/util.cpp
        ${PROJECT_ROOT}/src/client/network/asio_network_module.cpp
        )

add_library(client_obj STATIC ${CLIENT_TARGET_SOURCES})

target_link_libraries(
        client_obj
        PRIVATE project_options
        project_warnings
        fmt::fmt
        spdlog::spdlog
        asio::asio
        SQLite::SQLite
        cxxopts::cxxopts
        cereal::cereal
        ncurses::ncurses
        server_obj
)
