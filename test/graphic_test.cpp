#include "raylib.h"
#include "graphic_test.h"


void GraphicTest::SetUp() {
    InitWindow(800,600,"Graphic Test");
}

void GraphicTest::TearDown() {
    CloseWindow();
}