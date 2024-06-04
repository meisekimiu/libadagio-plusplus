#include "GracilisGame.h"
#include <iostream>
#include "raylib.h"
#include "../components/PlayerShip.h"
#include "../components/Position.h"
#include "../components/ShipRenderer.h"
#include "../systems/RemoveDead.h"
#include "../systems/ship.h"
#include "../systems/ShipRendererSystem.h"
#include "../systems/Wallop.h"
#include "../systems/WallopRendererSystem.h"

void GracilisGame::init() {
    std::cout << "GracilisGame init" << std::endl;
    registerSystem(ShipSystem);
    registerRenderer(ShipRendererSystem);
    registerSystem(WallopSystem);
    registerRenderer(WallopRendererSystem);
    registerSystem(RemoveDead);
}

void GracilisGame::loadContent(Adagio::SpriteBatch &spriteBatch) {
    spriteBatch.setClearColor({0, 0, 0, 255});
//    spriteBatch.clearColor = BLACK;
    shipTex = LoadTexture("assets/ship.png");
    wallopTex = LoadTexture("assets/wallop.png");
    const auto ship = registry.create();
    registry.emplace<PlayerShip>(ship, Vector2{0, 0}, &wallopTex);
    registry.emplace<Position>(ship, Vector2{320, 240});
    registry.emplace<ShipRenderer>(ship, &shipTex, 0, 0);
}

void GracilisGame::unloadContent() {
    std::cout << "GracilisGame quit" << std::endl;
    UnloadTexture(shipTex);
    UnloadTexture(wallopTex);
}
