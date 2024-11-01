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
  src/graphics/layer.cpp
  src/graphics/tilelayer.cpp
  src/graphics/animation.cpp
  test/graphic_test.cpp
  src/game/game.cpp
  src/game/gameobject.cpp
  src/game/level.cpp
  test/game_test.cpp
)

target_link_libraries(
  brutal_test
  GTest::gtest_main
  raylib glfw nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(brutal_test)

