macro(run_conan)
  if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake"
                  TLS_VERIFY ON
    )
  endif()

  include(${CMAKE_BINARY_DIR}/conan.cmake)
  include(${CMAKE_BINARY_DIR}/conan_paths.cmake)

  conan_cmake_configure(
    REQUIRES
    catch2/2.13.10
    fmt/10.1.0
    spdlog/1.12.0
    asio/1.28.1
    ncurses/6.4
    gtest/1.14.0
    sqlite3/3.42.0
    cxxopts/2.2.1
    cereal/1.3.2

    GENERATORS
    cmake_find_package
    cmake_paths
  )

  conan_cmake_autodetect(settings)

  conan_cmake_install(
    PATH_OR_REFERENCE
    .

    BUILD
    missing

    REMOTE
    conancenter

    SETTINGS
    ${settings}
  )

  find_package(fmt)
  find_package(Catch2)
  find_package(spdlog)
  find_package(asio)
  find_package(Curses)
  find_package(GTest)
  find_package(SQLite3)
  find_package(cxxopts)
  find_package(cereal)

endmacro()
