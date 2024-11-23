cmake_minimum_required(VERSION 3.20)
project(application)

find_package(SDL3 CONFIG REQUIRED)

file(
    GLOB_RECURSE
    PROJECT_HEADER_FILES src/*.h
    PROJECT_SOURCE_FILES src/*.c
)

add_executable(
    application
    ${PROJECT_HEADER_FILES}
    ${PROJECT_SOURCE_FILES}
)

target_link_libraries(
    application
    PRIVATE
    SDL3::SDL3
)

target_compile_features(
    application
    PRIVATE
    c_std_99
)

target_compile_options(
    application
    PRIVATE
    -Wall
    -Wconversion
    -Werror
    -Wextra
    -Wpedantic
)

# file(COPY data DESTINATION ${CMAKE_BINARY_DIR})
