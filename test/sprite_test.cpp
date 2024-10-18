#include <gtest/gtest.h>

#include "graphics/sprite.h"
#include "graphic_test.h"


class SpriteTest : public GraphicTest {

};

TEST_F(SpriteTest,TestLoadSprite) 
{

    Sprite new_sprite = Sprite();

    EXPECT_EQ(new_sprite.Load("assets/sprites/Archer/Archer.png"), Graphics::OK);
}