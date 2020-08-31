#cmake_minimum_required(VERSION 3.10)
#project(asciinem-test)
#
#if (CMAKE_COMPILER_IS_GNUCXX)
#    set(CMAKE_CXX_FLAGS "--coverage")
#endif ()
#
#add_library(Catch2::Catch IMPORTED INTERFACE)
#set_property(TARGET Catch2::Catch PROPERTY INTERFACE_INCLUDE_DIRECTORIES "${CATCH_INCLUDE_DIR}")
#
#set(TEST_TARGET_SOURCES
##        ${FMT_SOURCE_DIR}/format.cc
##        ${FMT_SOURCE_DIR}/os.cc
#        )
#
#set(TEST_SOURCES
#        ${TEST_TARGET_SOURCES}
#        main.cpp
#        )
#
#add_executable(${PROJECT_NAME} ${TEST_SOURCES})
#target_link_libraries(${PROJECT_NAME} Catch2::Catch)
#target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# automatically enable catch2 to generate ctest targets
if (CONAN_CATCH2_ROOT_DEBUG)
    include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else ()
    include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif ()

add_library(catch_main STATIC catch_main.cpp)
target_link_libraries(catch_main PUBLIC CONAN_PKG::catch2)
target_link_libraries(catch_main PRIVATE project_options)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE project_warnings project_options catch_main)

catch_discover_tests(
        tests
        TEST_PREFIX
        "unittests."
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

