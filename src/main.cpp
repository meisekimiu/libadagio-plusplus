#include "game/SandboxGame.h"
#include "game/states/GracilisGame.h"
#include "game/states/LeonaTestState.h"
#include "state/Runner.h"
#include <iostream>

#include "backends/raylib/RaylibGraphicsDevice.h"
#include "backends/raylib/RaylibGamepadHandler.h"
#include "backends/raylib/RaylibKeyboardHandler.h"
#include "backends/raylib/RaylibMouseHandler.h"
#include "backends/soloud/SoloudAudioDevice.h"


int main() {
    RaylibGraphicsDevice graphicsDevice;
    RaylibGamepadHandler gamepadHandler;
    RaylibKeyboardHandler keyboardHandler;
    RaylibMouseHandler mouseHandler;
    Adagio::SpriteBatch spriteBatch(&graphicsDevice);
    SoloudAudioDevice audioDevice;
    SandboxGame game(spriteBatch);
    game.audio.setAudioDevice(&audioDevice);
    game.input.addHandler(&gamepadHandler);
    game.input.addHandler(&keyboardHandler);
    game.input.addHandler(&mouseHandler);
    LeonaTestState leona{};
    GracilisGame state;
    Adagio::Runner runner(&game, dynamic_cast<Adagio::GameState *>(&state));
    runner.run();
    return EXIT_SUCCESS;
}
