project(asciinem-server LANGUAGES CXX VERSION 1.0.0)

set(TARGET_SOURCES
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
