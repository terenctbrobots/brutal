enable_testing()
find_package(GTest CONFIG REQUIRED)

include_directories(src)

add_executable(
  brutal_test
  src/helper.cpp
  test/helper_test.cpp
  src/graphics/sprite.cpp
  src/graphics/tileset.cpp
  src/graphics/tilesetpack.cpp
  src/graphics/tilelayer.cpp
  src/graphics/objectlayer.cpp
  src/graphics/animation.cpp
  src/graphics/bitmap.cpp
  test/graphic_test.cpp
  src/game/game.cpp
  src/game/gameobject.cpp
  src/game/level.cpp
  test/game_test.cpp
  test/ui_test.cpp
  test/lua_test.cpp
)

target_include_directories(brutal_test PRIVATE ${LUA_INCLUDE_DIR} ${LUABRIDGE3_INCLUDE_DIRS})

target_link_libraries(
  brutal_test
  PRIVATE
  GTest::gtest_main
  raylib glfw nlohmann_json
  spdlog::spdlog
 ${LUA_LIBRARIES}
 
)

include(GoogleTest)
gtest_discover_tests(brutal_test)

