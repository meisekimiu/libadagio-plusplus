#include "Game.h"

namespace Adagio {
    void Game::update() {
        frameDelta = GetFrameTime();
        gameTime = GetTime();
        stateMachine.update(this);
    }

    void Game::draw() {
        spriteBatch.begin();
        stateMachine.draw(this);
        spriteBatch.end();
    }

    bool Game::isRunning() const {
        return running;
    }

    double Game::getGameTime() const {
        return gameTime;
    }

    float Game::getFrameDelta() const {
        return frameDelta;
    }

    void Game::closeGame() {
        running = false;
    }

    void Game::loadContent() {

    }

    void Game::cleanup() {

    }

    void Game::unloadContent() {

    }
}
