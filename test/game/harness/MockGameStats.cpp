#include "MockGameStats.h"

bool MockGameStats::isRunning() const {
    return running;
}

void MockGameStats::closeGame() {
    running = false;
}

float MockGameStats::getFrameDelta() const {
    return static_cast<float>(gameTime - lastTickTime);
}

double MockGameStats::getGameTime() const {
    return gameTime;
}

void MockGameStats::advanceTime(double delta) {
    lastTickTime = gameTime;
    gameTime += delta;
}

void MockGameStats::reset() {
    lastTickTime = 0;
    gameTime = 0;
    running = true;
}
