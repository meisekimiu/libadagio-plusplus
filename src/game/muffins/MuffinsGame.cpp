#include "MuffinsGame.h"
#include <raylib.h>

namespace Muffins {
MuffinsGame::MuffinsGame(Adagio::SpriteBatch &sb) : Adagio::Game(sb) {}

void MuffinsGame::init() {
  InitWindow(1024, 768, "Muffin Mare");
  SetTargetFPS(60);

  input.actions.registerActionButton("HELP"_hs, Adagio::Input::Keyboard,
                                     KEY_F1);
  input.actions.registerActionButton("HELP"_hs, Adagio::Input::Mouse,
                                     MOUSE_BUTTON_MIDDLE);
  input.actions.registerActionButton("HELP"_hs, Adagio::Input::Gamepad,
                                     GAMEPAD_BUTTON_MIDDLE_LEFT);
  input.actions.registerActionButton("HELP"_hs, Adagio::Input::Gamepad,
                                     GAMEPAD_BUTTON_MIDDLE_RIGHT);

  input.actions.registerActionButton("EAT"_hs, Adagio::Input::Keyboard,
                                     KEY_SPACE);
  input.actions.registerActionButton("EAT"_hs, Adagio::Input::Mouse,
                                     MOUSE_BUTTON_LEFT);
  input.actions.registerActionButton("EAT"_hs, Adagio::Input::Gamepad,
                                     GAMEPAD_BUTTON_RIGHT_FACE_LEFT);
  input.actions.registerActionButton("EAT"_hs, Adagio::Input::Gamepad,
                                     GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
  input.actions.registerActionButton("EAT"_hs, Adagio::Input::Gamepad,
                                     GAMEPAD_BUTTON_RIGHT_FACE_UP);
  input.actions.registerActionButton("EAT"_hs, Adagio::Input::Gamepad,
                                     GAMEPAD_BUTTON_RIGHT_FACE_RIGHT);
}
} // namespace Muffins
