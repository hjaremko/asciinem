if (CONAN_CATCH2_ROOT_DEBUG)
    include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else ()
    include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif ()

include_directories(${PROJECT_ROOT}/include/server)
include_directories(${PROJECT_ROOT}/include/client)

add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC CONAN_PKG::catch2 CONAN_PKG::spdlog CONAN_PKG::asio CONAN_PKG::gtest CONAN_PKG::sqlite3)
target_link_libraries(catch_main PRIVATE project_options)

add_executable(server_tests
        server/network/clock_tests.cpp
        server/network/listener_tests.cpp
        server/network/queue_tests.cpp
        server/db/sqlite_tests.cpp
        ${PROJECT_ROOT}/src/server/network/asio_connection.cpp
        ${PROJECT_ROOT}/src/server/network/asio_server.cpp
        ${PROJECT_ROOT}/src/server/network/asio_listener.cpp
        ${PROJECT_ROOT}/src/server/network/message_queue.cpp
        ${PROJECT_ROOT}/src/server/db/sqlite_connection.cpp
        )
target_link_libraries(server_tests PRIVATE project_warnings project_options catch_main)

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
target_link_libraries(client_tests PRIVATE project_warnings project_options catch_main)

catch_discover_tests(
        client_tests
        TEST_PREFIX
        "client."
        EXTRA_ARGS
        -s
        --reporter=xml
        --out=tests.xml)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE project_warnings project_options catch_main)

catch_discover_tests(
        tests
        TEST_PREFIX
        "general."
        EXTRA_ARGS
        -s
        --reporter=xml
        --out=tests.xml)

add_executable(constexpr_tests constexpr_tests.cpp)
target_link_libraries(constexpr_tests PRIVATE project_options project_warnings catch_main)

catch_discover_tests(
        constexpr_tests
        TEST_PREFIX
        "constexpr."
        EXTRA_ARGS
        -s
        --reporter=xml
        --out=constexpr.xml)

add_executable(relaxed_constexpr_tests constexpr_tests.cpp)
target_link_libraries(relaxed_constexpr_tests PRIVATE project_options project_warnings catch_main)
target_compile_definitions(relaxed_constexpr_tests PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)

catch_discover_tests(
        relaxed_constexpr_tests
        TEST_PREFIX
        "relaxed_constexpr."
        EXTRA_ARGS
        -s
        --reporter=xml
        --out=relaxed_constexpr.xml)
