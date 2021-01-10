if (CONAN_CATCH2_ROOT_DEBUG)
    include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else ()
    include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif ()

add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(
        catch_main PUBLIC
        CONAN_PKG::catch2
        CONAN_PKG::spdlog
        CONAN_PKG::asio
        CONAN_PKG::gtest
        CONAN_PKG::sqlite3
        CONAN_PKG::cereal
)

target_link_libraries(catch_main PRIVATE project_options)

add_executable(server_tests
        server/network/clock_tests.cpp
        server/network/listener_tests.cpp
        server/network/queue_tests.cpp
        server/network/connection_manager_tests.cpp
        server/db/sqlite_tests.cpp
        server/db/mappers/backpack_mapper_test.cpp
        server/db/mappers/player_mapper_test.cpp
        server/db/mappers/item_mapper_test.cpp
        server/domain/collision_checker_tests.cpp
        server/domain/location_tests.cpp
        server/domain/player_tests.cpp
        server/domain/monster_tests.cpp
        )

target_link_libraries(server_tests
        PRIVATE project_warnings
        project_options
        catch_main
        server_obj
        )

catch_discover_tests(
        server_tests
        TEST_PREFIX
        "server."
        EXTRA_ARGS
        -s
        --reporter=xml
        --out=tests.xml)

add_executable(client_tests
        client/tests.cpp
        )
target_link_libraries(client_tests
        PRIVATE project_warnings
        project_options
        catch_main)

catch_discover_tests(
        client_tests
        TEST_PREFIX
        "client."
        EXTRA_ARGS
        -s
        --reporter=xml
        --out=tests.xml)

#add_executable(common common\test.cpp)
#target_link_libraries(common PRIVATE project_warnings project_options catch_main)
#
#catch_discover_tests(
#        tests
#        TEST_PREFIX
#        "common."
#        EXTRA_ARGS
#        -s
#        --reporter=xml
#        --out=tests.xml)
