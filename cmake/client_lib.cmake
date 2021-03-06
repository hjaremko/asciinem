set(CLIENT_TARGET_SOURCES
        ${PROJECT_ROOT}/src/client/util.cpp
        ${PROJECT_ROOT}/src/client/network/asio_network_module.cpp
        )

add_library(client_obj STATIC ${CLIENT_TARGET_SOURCES})

target_link_libraries(
        client_obj
        PRIVATE project_options
        project_warnings
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::asio
        CONAN_PKG::sqlite3
        CONAN_PKG::cxxopts
        CONAN_PKG::cereal
        CONAN_PKG::ncurses
        server_obj
)
