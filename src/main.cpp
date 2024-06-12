#include "game/SandboxGame.h"
#include "game/states/GracilisGame.h"
#include "game/states/LeonaTestState.h"
#include "state/Runner.h"
#include <iostream>

#include "backends/raylib/RaylibGraphicsDevice.h"

int main() {
  RaylibGraphicsDevice graphicsDevice;
  Adagio::SpriteBatch spriteBatch(&graphicsDevice);
  SandboxGame game(spriteBatch);
  LeonaTestState leona{};
  GracilisGame state;
  Adagio::Runner runner(&game, dynamic_cast<Adagio::GameState *>(&state));
  runner.run();
  return EXIT_SUCCESS;
}
