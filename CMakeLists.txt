cmake_minimum_required(VERSION 3.5.0)
project(brutal VERSION 0.1.0 LANGUAGES C CXX)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)
include_directories(../raylib/src)

file(GLOB_RECURSE sources      src/*.cpp)

add_executable(brutal ${sources})

target_link_directories(brutal PUBLIC ../raylib/src)
target_link_libraries(brutal -lraylib)

