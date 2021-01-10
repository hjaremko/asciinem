set(SERVER_TARGET_SOURCES
        ${PROJECT_ROOT}/src/server/util.cpp
        ${PROJECT_ROOT}/src/server/domain/armor.cpp
        ${PROJECT_ROOT}/src/server/domain/collision_checker.cpp
        ${PROJECT_ROOT}/src/server/domain/entity.cpp
        ${PROJECT_ROOT}/src/server/domain/health_potion.cpp
        ${PROJECT_ROOT}/src/server/domain/item.cpp
        ${PROJECT_ROOT}/src/server/domain/location.cpp
        ${PROJECT_ROOT}/src/server/domain/monster.cpp
        ${PROJECT_ROOT}/src/server/domain/player.cpp
        ${PROJECT_ROOT}/src/server/domain/weapon.cpp
        ${PROJECT_ROOT}/src/server/domain/strategies/random_move_strategy.cpp
        ${PROJECT_ROOT}/src/server/domain/strategies/still_strategy.cpp
        ${PROJECT_ROOT}/src/server/domain/util/money.cpp
        ${PROJECT_ROOT}/src/server/network/asio_connection.cpp
        ${PROJECT_ROOT}/src/server/network/asio_server.cpp
        ${PROJECT_ROOT}/src/server/network/asio_listener.cpp
        ${PROJECT_ROOT}/src/server/network/message_queue.cpp
        ${PROJECT_ROOT}/src/server/network/asio_manager.cpp
        ${PROJECT_ROOT}/src/server/db/sqlite_connection.cpp
        )

add_library(server_obj STATIC ${SERVER_TARGET_SOURCES})

target_link_libraries(
        server_obj
        PRIVATE project_options
        project_warnings
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::asio
        CONAN_PKG::cxxopts
        CONAN_PKG::cereal
        CONAN_PKG::sqlite3
)
