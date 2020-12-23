project(asciinem-client LANGUAGES CXX VERSION 1.0.0)

include_directories(${PROJECT_ROOT}/include/)

set(TARGET_SOURCES
        network/asio_network_module.cpp
        ${PROJECT_ROOT}/src/client/util.cpp
        ${PROJECT_ROOT}/src/server/network/message_queue.cpp
        ${PROJECT_ROOT}/src/server/network/asio_connection.cpp
        )

add_executable(${PROJECT_NAME}
        main.cpp
        ${TARGET_SOURCES}
        )

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE project_options
        project_warnings
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::asio
        CONAN_PKG::ncurses
        CONAN_PKG::cxxopts
        CONAN_PKG::cereal
)
