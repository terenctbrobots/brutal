cmake_minimum_required(VERSION 3.5.0)
project(brutal VERSION 0.1.0 LANGUAGES C CXX)

include(~/vcpkg/scripts/buildsystems/vcpkg.cmake)

file(GLOB_RECURSE sources      src/*.cpp)

find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

add_executable(brutal ${sources})

target_link_libraries(brutal PRIVATE raylib glfw nlohmann_json spdlog::spdlog)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(${CMAKE_SOURCE_DIR}/test/CMakeLists.txt)
endif()