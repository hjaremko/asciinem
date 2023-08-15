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
        fmt::fmt
        spdlog::spdlog
        asio::asio
        cxxopts::cxxopts
        cereal::cereal
        SQLite::SQLite
)
