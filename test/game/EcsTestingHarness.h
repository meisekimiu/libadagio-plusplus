#ifndef GL_ADAGIO_ECSTESTINGHARNESS_H
#define GL_ADAGIO_ECSTESTINGHARNESS_H

#include "../../src/graphics/SpriteBatch.h"
#include "../../src/state/RenderingServices.h"
#include "harness/EcsMockGraphicsDevice.h"
#include "harness/MockGameStats.h"
#include "entt/entt.hpp"
#include "../../src/state/EntityGameState.h"
#include "../../src/state/StateMachine.h"

class EcsTestingHarness {
public:
    EcsMockGraphicsDevice graphicsDevice;
    Adagio::SpriteBatch spriteBatch{&graphicsDevice};
    MockGameStats stats;
    entt::registry registry;
    Adagio::RenderingServices renderingServices{};
    Adagio::StateMachine *stateMachine;

    EcsTestingHarness();

    void reset();

    void testRendererFrame(Adagio::RendererFn renderer);
    void testSystemFrame(Adagio::SystemFn system);
};


#endif //GL_ADAGIO_ECSTESTINGHARNESS_H
