project(asciinem-client LANGUAGES CXX VERSION 1.0.0)

include_directories(${PROJECT_ROOT}/include/)

set(TARGET_SOURCES
        network/asio_network_module.cpp
        ${PROJECT_ROOT}/src/client/util.cpp
        ${PROJECT_ROOT}/src/server/network/message_queue.cpp
        ${PROJECT_ROOT}/src/server/network/asio_connection.cpp
        ${PROJECT_ROOT}/src/server/domain/entity.cpp
        ${PROJECT_ROOT}/src/server/domain/player.cpp
        ${PROJECT_ROOT}/src/server/domain/health_potion.cpp
        ${PROJECT_ROOT}/src/server/domain/item.cpp
        ${PROJECT_ROOT}/src/server/domain/weapon.cpp
        ${PROJECT_ROOT}/src/server/domain/armor.cpp
        ${PROJECT_ROOT}/src/server/domain/util/money.cpp
        ${PROJECT_ROOT}/src/server/domain/monster.cpp
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
