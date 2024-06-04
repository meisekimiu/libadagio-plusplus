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

void GracilisGame::loadContent(Adagio::SpriteBatch &spriteBatch, Adagio::RenderingServices &services) {
    spriteBatch.setClearColor({0, 0, 0, 255});
    shipTex = services.textureManager->load("assets/ship.png");
    wallopTex = services.textureManager->load("assets/wallop.png");
    const auto ship = registry.create();
    registry.emplace<PlayerShip>(ship, Adagio::Vector2d{0, 0}, wallopTex);
    registry.emplace<Position>(ship, Adagio::Vector2d{320, 240});
    registry.emplace<ShipRenderer>(ship, shipTex, 0, 0);
}

void GracilisGame::unloadContent(Adagio::RenderingServices &services) {
    std::cout << "GracilisGame quit" << std::endl;
    services.textureManager->unload(shipTex);
    services.textureManager->unload(wallopTex);
}
