#include "Game.h"

#include <utility>

namespace Adagio {
    Game::Game(SpriteBatch &spriteBatch) : spriteBatch(std::move(spriteBatch)) {}

    void Game::update() {
        frameDelta = GetFrameTime();
        gameTime = GetTime();
        input.update();
        stateMachine.update(gameServices);
    }

    void Game::draw() {
        spriteBatch.begin();
        stateMachine.draw();
        spriteBatch.end();
    }

    bool Game::isRunning() const { return running; }

    double Game::getGameTime() const { return gameTime; }

    float Game::getFrameDelta() const { return frameDelta; }

    void Game::closeGame() { running = false; }

    void Game::loadContent() {}

    void Game::cleanup() {}

    void Game::unloadContent() {}

} // namespace Adagio
