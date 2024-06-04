#include "LeonaTestState.h"

void LeonaTestState::init() {
    leonaPos = {0, 0};
}

void LeonaTestState::loadContent(Adagio::SpriteBatch &spriteBatch) {
    spriteBatch.setClearColor({0, 0, 255, 255});
    leonaTex = spriteBatch.getGraphicsDevice()->getTextureManager()->load("assets/leona_smile.png");
}

void LeonaTestState::update(Adagio::GameStats &stats, Adagio::StateMachine *gameStates) {
    auto pos = GetMousePosition();
    leonaPos = {pos.x, pos.y};
}

void LeonaTestState::draw(Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) {
    auto txt = spriteBatch.drawText("Lookit Leona", {0, 0}, 10);
    txt->fontSize = 36;
    auto leonaSprite = spriteBatch.draw(leonaTex, leonaPos, 0);
    leonaSprite->origin.x = leonaTex.getWidth() / 2;
    leonaSprite->origin.y = leonaTex.getHeight() / 2;
}

void LeonaTestState::unloadContent() {
    // TODO: we need to pass texture manager to unloadContent so we can actually unload stuff
}
