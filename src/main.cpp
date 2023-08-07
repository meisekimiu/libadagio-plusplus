#include "raylib.h"
#include <iostream>

int main() {
    InitWindow(640, 480, "Raylib Test");
    while (!WindowShouldClose()) {}
    CloseWindow();
    return EXIT_SUCCESS;
}
