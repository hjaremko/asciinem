macro(run_conan)
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.16.1/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
  endif()

  include(${CMAKE_BINARY_DIR}/conan.cmake)

  conan_check(VERSION 1.0.0 REQUIRED)
  conan_add_remote(
    NAME
    conancenter
    URL
    https://center.conan.io)

  conan_cmake_run(
    REQUIRES
    ${CONAN_EXTRA_REQUIRES}
    catch2/2.13.7
    fmt/8.0.1
    spdlog/1.9.2
    asio/1.19.2
    ncurses/6.2
    gtest/1.10.0
    sqlite3/3.36.0
    cxxopts/2.2.1
    cereal/1.3.0
    OPTIONS
    ${CONAN_EXTRA_OPTIONS}
    BASIC_SETUP
    CMAKE_TARGETS # individual targets to link to
    BUILD
    missing)
endmacro()
