#include "TestGame.h"

TestGame::TestGame(Adagio::SpriteBatch sb) : Adagio::Game(sb) {}

void TestGame::init() {
    calledInit = true;
}

void TestGame::loadContent() {
    calledLoadContent = true;
}

void TestGame::unloadContent() {
    calledUnloadContent = true;
}

void TestGame::cleanup() {
    calledCleanup = true;
}


