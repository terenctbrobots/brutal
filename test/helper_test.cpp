#include <gtest/gtest.h>
#include "helper.h"

TEST(HelperTest, TestGetJSONFilename) {

  string testString;
  
  testString = GetJSONFilename("assets/archer.png");
  EXPECT_EQ(testString,"assets/archer.json");

  testString = GetJSONFilename("assets/archer.jpeg");
  EXPECT_EQ(testString,"assets/archer.json");

  testString = GetJSONFilename("assets/archer");
  EXPECT_EQ(testString,"");

  testString = GetJSONFilename("ass.mah/archer.png");
  EXPECT_EQ(testString,"ass.mah/archer.json");
}