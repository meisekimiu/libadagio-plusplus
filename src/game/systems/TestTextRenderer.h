#ifndef GL_ADAGIO_TESTTEXTRENDERER_H
#define GL_ADAGIO_TESTTEXTRENDERER_H

#define LIBERATION_MONO_16 "assets/liberation-mono-16.fnt"_hs

#include "../../graphics/SpriteBatch.h"
#include "../../state/GameState.h"
#include "entt/entt.hpp"

void TestTextRenderer(entt::registry &registry, Adagio::SpriteBatch &spriteBatch,
                      Adagio::RenderingServices &services);

#endif //GL_ADAGIO_TESTTEXTRENDERER_H
