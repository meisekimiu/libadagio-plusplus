#include "EcsTestingHarness.h"

EcsTestingHarness::EcsTestingHarness() {
    renderingServices = {&spriteBatch, graphicsDevice.getTextureManager(), &stats};
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
