#include "GracilisGame.h"
#include "../components/Enemy.h"
#include "../components/PlayerShip.h"
#include "../components/Position.h"
#include "../components/Sprite.h"
#include "../components/SpriteClip.h"
#include "../components/UserProjectile.h"
#include "../systems/AnimateSprite.h"
#include "../systems/ApplyVelocity.h"
#include "../systems/RemoveDead.h"
#include "../systems/RenderSprite.h"
#include "../systems/Wallop.h"
#include "../systems/ship.h"
#include "../systems/WallopEvents.h"
#include "../systems/DetectCollision.h"
#include "../systems/EnemyEvents.h"
#include "../components/events/MessageInbox.h"
#include "../systems/TestTextRenderer.h"
#include <iostream>

void GracilisGame::init() {
    std::cout << "GracilisGame init" << std::endl;
    registerSystem(AnimateSprite);
    registerRenderer(TestTextRenderer);
    registerRenderer(RenderSprite);
    registerSystem(ApplyVelocity);
    registerSystem(ShipSystem);
    registerSystem(WallopSystem);
    registerSystem(DetectCollision<UserProjectile, Enemy>);
    registerSystem(WallopEventsSystem);
    registerSystem(EnemyEventsSystem);
    registerSystem(RemoveDead);
}

void GracilisGame::loadContent(Adagio::SpriteBatch &spriteBatch,
                               Adagio::RenderingServices &services) {
    spriteBatch.setClearColor({0, 0, 0, 255});
    services.fontManager->load("assets/liberation-mono-16.fnt");
    shipTex = services.textureManager->load("assets/ship.png");
    wallopTex = services.textureManager->load("assets/wallop.png");
    auto spinnyTex = services.textureManager->load("assets/spinny.png");
    Adagio::SpriteAnimationFrame wallopFrames[] = {
            {0.083333, Adagio::RectI{0, 0, 64, 56}},
            {0.083333, Adagio::RectI{64, 0, 64, 56}},
            {0.083333, Adagio::RectI{64 * 2, 0, 64, 56}},
            {0.083333, Adagio::RectI{64 * 3, 0, 64, 56}},
    };
    services.animationLibrary->createAnimation("WALLOP"_hs, 4, wallopFrames);


    Adagio::SpriteAnimationFrame spinnyFrames[] = {
            {0.083333, Adagio::RectI{0, 0, 59, 58}},
            {0.083333, Adagio::RectI{59, 0, 59, 58}},
            {0.083333, Adagio::RectI{59 * 2, 0, 59, 58}},
            {0.083333, Adagio::RectI{59 * 3, 0, 59, 58}},
    };
    services.animationLibrary->createAnimation("SPINNY"_hs, 4, spinnyFrames);
    const auto spinny = registry.create();
    registry.emplace<Enemy>(spinny, 5);
    registry.emplace<MessageInbox>(spinny);
    registry.emplace<Position>(spinny, Adagio::Vector2d{320, 100});
    registry.emplace<Sprite>(spinny, spinnyTex);
    registry.emplace<SpriteClip>(spinny);
    registry.emplace<CollisionRadius>(spinny, Adagio::Vector2d{59.0 / 2, 58.0 / 2}, 30);
    SpriteAnimation &spinnyAnimation = registry.emplace<SpriteAnimation>(spinny, "SPINNY"_hs);
    spinnyAnimation.loop = true;


    const auto ship = registry.create();
    registry.emplace<PlayerShip>(ship, Adagio::Vector2d{0, 0});
    registry.emplace<Position>(ship, Adagio::Vector2d{320, 240});
    registry.emplace<Sprite>(ship, shipTex, Adagio::Vector2d{0, 0}, 0);
    registry.emplace<SpriteClip>(ship);
    SpriteAnimation &animation = registry.emplace<SpriteAnimation>(ship, "SHIP"_hs);
    animation.loop = true;
    Adagio::SpriteAnimationFrame shipFrames[] = {
            {0.083333, Adagio::RectI{0, 0, 56, 89}},
            {0.083333, Adagio::RectI{56, 0, 56, 89}},
            {0.083333, Adagio::RectI{56 * 2, 0, 56, 89}},
            {0.083333, Adagio::RectI{56 * 3, 0, 56, 89}},
    };
    services.animationLibrary->createAnimation("SHIP"_hs, 4, shipFrames);

    services.audioService->getAudioLibrary().loadSample("assets/relax.wav");
}

void GracilisGame::unloadContent(Adagio::RenderingServices &services) {
    std::cout << "GracilisGame quit" << std::endl;
    services.textureManager->unload(shipTex);
    services.textureManager->unload(wallopTex);
}
