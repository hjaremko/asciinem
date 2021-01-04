project(asciinem-server LANGUAGES CXX VERSION 1.0.0)

include_directories(${PROJECT_ROOT}/include/)

set(TARGET_SOURCES
        util.cpp
        domain/armor.cpp
        domain/entity.cpp
        domain/item.cpp
        domain/location.cpp
        domain/monster.cpp
        domain/player.cpp
        domain/weapon.cpp
        domain/strategies/random_move_strategy.cpp
        domain/strategies/still_strategy.cpp
        domain/util/money.cpp
        network/asio_connection.cpp
        network/asio_server.cpp
        network/asio_listener.cpp
        network/message_queue.cpp
        network/asio_manager.cpp
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
        CONAN_PKG::sqlite3
        CONAN_PKG::cxxopts
        CONAN_PKG::cereal
)
