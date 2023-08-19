#include <iostream>
#include "game/SandboxGame.h"
#include "game/states/LeonaTestState.h"
#include "game/states/GracilisGame.h"
#include "state/Runner.h"

int main() {
    SandboxGame game;
//    LeonaTestState state;
    GracilisGame state;
    Adagio::Runner runner(&game, &state);
    runner.run();
    return EXIT_SUCCESS;
}
