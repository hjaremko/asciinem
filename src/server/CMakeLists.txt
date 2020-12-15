project(asciinem-server LANGUAGES CXX VERSION 1.0.0)

include_directories(${PROJECT_ROOT}/include/server/)

set(TARGET_SOURCES
        network/asio_connection.cpp
        network/asio_server.cpp
        network/asio_listener.cpp
        network/message_queue.cpp
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
)
