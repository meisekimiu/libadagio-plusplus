#include "EcsTestingHarness.h"

EcsTestingHarness::EcsTestingHarness() {
    input.addHandler(&mockInputs.gamepad);
    input.addHandler(&mockInputs.keyboard);
    input.addHandler(&mockInputs.mouse);
    gameServices.messageDispatchService = &messageService;
    gameServices.stats = &stats;
    gameServices.resources.textureManager = spriteBatch.getGraphicsDevice()->getTextureManager();
    gameServices.resources.animationLibrary = &animationLibrary;
    gameServices.input = &input;
    renderingServices = {&spriteBatch, graphicsDevice.getTextureManager(), &stats, &animationLibrary};
    stateMachine = new Adagio::StateMachine(&spriteBatch, &renderingServices);
    registry.ctx().emplace<Adagio::MessageDispatchService *>(&messageService);
}

void EcsTestingHarness::reset() {
    spriteBatch.begin();
    spriteBatch.end();
    registry.clear();
    stats.reset();
}

void EcsTestingHarness::testRendererFrame(Adagio::RendererFn renderer) {
    spriteBatch.begin();
    renderer(registry, spriteBatch, renderingServices);
    spriteBatch.end();
}

void EcsTestingHarness::testSystemFrame(Adagio::SystemFn system) {
    system(registry, gameServices, stateMachine);
}
