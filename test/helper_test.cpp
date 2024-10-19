#include <gtest/gtest.h>
#include "helper.h"
namespace {

TEST(HelperTest, TestGetJSONFilename) 
{

  std::string testString;
  
  testString = GetJSONFilename("assets/archer.png");
  EXPECT_EQ(testString,"assets/archer.json");

  testString = GetJSONFilename("assets/archer.jpeg");
  EXPECT_EQ(testString,"assets/archer.json");

  testString = GetJSONFilename("assets/archer");
  EXPECT_EQ(testString,"");

  testString = GetJSONFilename("ass.mah/archer.png");
  EXPECT_EQ(testString,"ass.mah/archer.json");
}

TEST(HelperTest, TestLoadTextFile) 
{
  std::optional<std::string> test_buffer = LoadTextFile("testdata/textfile.txt");

  EXPECT_NE(test_buffer, std::nullopt);

  EXPECT_EQ(test_buffer.value(),"This is a test");
}
  
}
