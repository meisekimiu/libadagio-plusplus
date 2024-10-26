#include "TestTextRenderer.h"

void TestTextRenderer(entt::registry &registry, Adagio::SpriteBatch &spriteBatch,
                      Adagio::RenderingServices &services) {
    auto text = spriteBatch.drawText("Hello World", {0, 0});
    text->font = services.fontManager->getFont(LIBERATION_MONO_16);
    text->fontSize = 19;
}
