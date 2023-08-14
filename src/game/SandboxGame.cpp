#include "SandboxGame.h"

void SandboxGame::init() {
    InitWindow(640, 480, "Raylib Test");
    SetTargetFPS(60);
}

void SandboxGame::loadContent() {
    // load game statez
}

void SandboxGame::cleanup() {
    CloseWindow();
}
