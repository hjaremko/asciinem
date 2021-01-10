project(asciinem-server LANGUAGES CXX VERSION 1.0.0)

add_executable(${PROJECT_NAME}
        main.cpp
        )

target_link_libraries(
        ${PROJECT_NAME}
        PUBLIC server_obj
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE project_options
        project_warnings
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        CONAN_PKG::asio
        CONAN_PKG::cxxopts
        CONAN_PKG::cereal
        CONAN_PKG::sqlite3
)
