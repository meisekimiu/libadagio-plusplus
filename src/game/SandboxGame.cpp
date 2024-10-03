#include "SandboxGame.h"

SandboxGame::SandboxGame(Adagio::SpriteBatch &sb) : Adagio::Game(sb) {}

void SandboxGame::init() {
    InitWindow(640, 480, "Raylib Test");
    SetTargetFPS(60);
    input.gamepad.createAxisPair("move"_hs, GAMEPAD_AXIS_LEFT_X, GAMEPAD_AXIS_LEFT_Y);
    input.gamepad.setAxisPairDeadzone("move"_hs, 0.1);
    input.gamepad.setAxisPairMaxzone("move"_hs, 1);
    input.actions.registerActionButton("fire"_hs, Adagio::Input::Keyboard, KEY_SPACE);
    input.actions.registerActionButton("fire"_hs, Adagio::Input::Gamepad, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
    input.actions.registerActionDirectionKeys("move"_hs, KEY_LEFT, KEY_DOWN, KEY_UP, KEY_RIGHT);
    input.actions.registerActionDirectionAxes("move"_hs, "move"_hs);
}

void SandboxGame::loadContent() {
    // load game statez
}

void SandboxGame::cleanup() { CloseWindow(); }
