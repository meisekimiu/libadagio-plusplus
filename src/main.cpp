#include "game/SandboxGame.h"
#include "game/states/GracilisGame.h"
#include "game/states/LeonaTestState.h"
#include "state/Runner.h"
#include <iostream>

#include "backends/raylib/RaylibGraphicsDevice.h"
#include "backends/raylib/RaylibGamepadHandler.h"
#include "backends/raylib/RaylibKeyboardHandler.h"
#include "backends/raylib/RaylibMouseHandler.h"


int main() {
    RaylibGraphicsDevice graphicsDevice;
    RaylibGamepadHandler gamepadHandler;
    RaylibKeyboardHandler keyboardHandler;
    RaylibMouseHandler mouseHandler;
    Adagio::SpriteBatch spriteBatch(&graphicsDevice);
    SandboxGame game(spriteBatch);
    game.input.addHandler(&gamepadHandler);
    game.input.addHandler(&keyboardHandler);
    game.input.addHandler(&mouseHandler);
    LeonaTestState leona{};
    GracilisGame state;
    Adagio::Runner runner(&game, dynamic_cast<Adagio::GameState *>(&state));
    runner.run();
    return EXIT_SUCCESS;
}
