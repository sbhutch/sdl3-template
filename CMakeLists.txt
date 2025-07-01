cmake_minimum_required(VERSION 3.20)
project(application)

find_package(SDL3 CONFIG REQUIRED)

file(
    GLOB_RECURSE
    PROJECT_HEADERS src/*.h
    PROJECT_SOURCES src/*.c
)

add_executable(
    application
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
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

# file(COPY data DESTINATION ${CMAKE_BINARY_DIR})
