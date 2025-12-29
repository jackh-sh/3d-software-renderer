cmake_minimum_required(VERSION 3.10...3.30)

project(App)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Use Homebrew SDL2 on macOS
set(SDL2_DIR /opt/homebrew/lib/cmake/SDL2)
find_package(SDL2 REQUIRED)

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")
add_executable(App ${SOURCES})

target_include_directories(App PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(App PRIVATE SDL2::SDL2)