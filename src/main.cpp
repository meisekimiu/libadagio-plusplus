#include <iostream>
#include "game/SandboxGame.h"
#include "game/states/LeonaTestState.h"
#include "state/Runner.h"

int main() {
    SandboxGame game;
    LeonaTestState state;
    Adagio::Runner runner(&game, &state);
    runner.run();
    return EXIT_SUCCESS;
}
