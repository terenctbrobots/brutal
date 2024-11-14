#include "helper.h"

#include <gtest/gtest.h>

#include <fstream>

#include "nlohmann/json.hpp"
using json = nlohmann::json;
namespace {

TEST(HelperTest, TestLoadTextFile) {
    std::optional<std::string> test_buffer = LoadTextFile("testdata/textfile.txt");

    EXPECT_NE(test_buffer, std::nullopt);

    EXPECT_EQ(test_buffer.value(), "This is a test");
}

TEST(HelperTest, TestJSONParsing) {
    std::ifstream test_json("testdata/Knight.json");

    json parsed = json::parse(test_json);

    EXPECT_EQ(parsed["width"], 100);

    // Test if NOT exists
    EXPECT_EQ(parsed["meh"], nullptr);

    json array = parsed["animation"];

    for (auto& el : array.items()) {
        std::cout << "key: " << el.key() << ", value: " << el.value() << std::endl;

        std::cout << "frames " << el.value()["frames"] << std::endl;
    }

    // u_int16_t max = (u_int16_t)65536;
    // std::cout << max << std::endl;
}

TEST(HelperTest, TestOverloads) {
    Vector2 one = {5, 5};
    Vector2 two = {2, 2};

    Vector2 three = one + two;

    EXPECT_EQ(three.x, 7);
    EXPECT_EQ(three.y, 7);

    Vector2 four = one - two;
    EXPECT_EQ(four.x, 3);
}

}  // namespace
