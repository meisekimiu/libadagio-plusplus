#ifndef GL_ADAGIO_ECSTESTINGHARNESS_H
#define GL_ADAGIO_ECSTESTINGHARNESS_H

#include "../../src/graphics/SpriteBatch.h"
#include "../../src/state/EntityGameState.h"
#include "../../src/state/RenderingServices.h"
#include "../../src/state/StateMachine.h"
#include "../../src/event/MessageDispatchService.h"
#include "entt/entt.hpp"
#include "harness/EcsMockGraphicsDevice.h"
#include "harness/MockGameStats.h"

class EcsTestingHarness {
public:
    EcsMockGraphicsDevice graphicsDevice;
    Adagio::SpriteBatch spriteBatch{&graphicsDevice};
    MockGameStats stats;
    entt::registry registry;
    Adagio::GameServices gameServices;
    Adagio::RenderingServices renderingServices{};
    Adagio::StateMachine *stateMachine;
    Adagio::MessageDispatchService messageService;

    EcsTestingHarness();

    void reset();

    void testRendererFrame(Adagio::RendererFn renderer);

    void testSystemFrame(Adagio::SystemFn system);
};

#endif // GL_ADAGIO_ECSTESTINGHARNESS_H
