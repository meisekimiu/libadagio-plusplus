#include "EmptyGameState.h"

void EmptyGameState::init() {
    initCalled = true;
}

void EmptyGameState::loadContent(Adagio::SpriteBatch &sb, Adagio::RenderingServices &services) {
    loadContentCalled = true;
}

void EmptyGameState::update(Adagio::GameStats &stats, Adagio::StateMachine *gameStates) {
    frameDelta = stats.getFrameDelta();
    gameTime = stats.getGameTime();
    updateCalled = true;
}

void EmptyGameState::draw(Adagio::SpriteBatch &sb, Adagio::RenderingServices &services) {
    drawCalled = true;
}

void EmptyGameState::pause() {
    pauseCalled = true;
}

void EmptyGameState::resume() {
    resumeCalled = true;
}

void EmptyGameState::unloadContent(Adagio::RenderingServices &_services) {
    unloadContentCalled = true;
}

void EmptyGameState::cleanup() {
    cleanupCalled = true;
}

bool EmptyGameState::calledInit() const {
    return initCalled;
}

bool EmptyGameState::calledCleanup() const {
    return cleanupCalled;
}

bool EmptyGameState::calledLoadContent() const {
    return loadContentCalled;
}

bool EmptyGameState::calledUnloadContent() const {
    return unloadContentCalled;
}

bool EmptyGameState::calledUpdate() const {
    return updateCalled;
}

bool EmptyGameState::calledDraw() const {
    return drawCalled;
}

bool EmptyGameState::calledPause() const {
    return pauseCalled;
}

bool EmptyGameState::calledResume() const {
    return resumeCalled;
}

float EmptyGameState::lastFrameTime() const {
    return frameDelta;
}

double EmptyGameState::lastGameTime() const {
    return gameTime;
}

void EmptyGameState::reset() {
    frameDelta = -1;
    gameTime = -1;
    initCalled = false;
    loadContentCalled = false;
    updateCalled = false;
    drawCalled = false;
    pauseCalled = false;
    resumeCalled = false;
    unloadContentCalled = false;
    cleanupCalled = false;
}
