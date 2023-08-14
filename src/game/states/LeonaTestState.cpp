#include "LeonaTestState.h"

void LeonaTestState::init() {
    leonaPos = {0, 0};
}

void LeonaTestState::loadContent(Adagio::SpriteBatch &spriteBatch) {
    spriteBatch.clearColor = BLUE;
    leonaTex = LoadTexture("assets/leona_smile.png");
}

void LeonaTestState::update(Adagio::GameStats &stats, Adagio::StateMachine *gameStates) {
    leonaPos = GetMousePosition();
}

void LeonaTestState::draw(Adagio::SpriteBatch &spriteBatch, const Adagio::GameStats &stats) {
    auto txt = spriteBatch.drawText("Lookit Leona", {0, 0}, 10);
    txt->fontSize = 36;
    auto leonaSprite = spriteBatch.draw(leonaTex, leonaPos, 0);
    leonaSprite->origin.x = leonaTex.width / 2;
    leonaSprite->origin.y = leonaTex.height / 2;
}

void LeonaTestState::unloadContent() {
    UnloadTexture(leonaTex);
}
