#include "EcsTestingHarness.h"

EcsTestingHarness::EcsTestingHarness() {
    renderingServices = {&spriteBatch, graphicsDevice.getTextureManager(), &stats};
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
    system(registry, stats, stateMachine);
}
