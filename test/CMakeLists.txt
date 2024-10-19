enable_testing()
find_package(GTest CONFIG REQUIRED)

include_directories(src)

add_executable(
  brutal_test
  src/helper.cpp
  test/helper_test.cpp
  test/sprite_test.cpp
  src/graphics/sprite.cpp
)

target_link_libraries(
  brutal_test
  GTest::gtest_main
  raylib glfw nlohmann_json
)

include(GoogleTest)
gtest_discover_tests(brutal_test)

