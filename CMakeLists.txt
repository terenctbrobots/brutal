cmake_minimum_required(VERSION 3.5.0)
project(brutal VERSION 0.1.0 LANGUAGES C CXX)

include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)

file(GLOB_RECURSE sources      src/*.cpp)

find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(EnTT CONFIG REQUIRED)

pkg_check_modules(LuaJIT REQUIRED IMPORTED_TARGET luajit)

add_compile_options("$<$<CONFIG:DEBUG>:-DDEBUG>")

add_executable(brutal ${sources})

find_path(LUABRIDGE3_INCLUDE_DIRS "luabridge3/LuaBridge/Array.h")
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")

target_compile_definitions(brutal PRIVATE NOUNIT)
target_include_directories(brutal PRIVATE ${LUABRIDGE3_INCLUDE_DIRS} ${RAYGUI_INCLUDE_DIRS})
target_link_libraries(brutal PRIVATE raylib glfw nlohmann_json spdlog::spdlog PkgConfig::LuaJIT EnTT::EnTT)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    include(${CMAKE_SOURCE_DIR}/test/CMakeLists.txt)
endif()