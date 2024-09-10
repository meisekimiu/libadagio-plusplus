#include "SpriteBatch.h"
#include <algorithm>
#include <raylib.h>

namespace Adagio {
    int SpriteBatch::queueReservation = 128;

    SpriteBatch::SpriteBatch(GraphicsDevice *gd) {
        graphicsDevice = gd;
        renderingQueue.reserve(SpriteBatch::queueReservation);
    }

    void SpriteBatch::begin() {
        graphicsDevice->begin();
        renderingQueue.clear();
        spritePool.begin();
        textPool.begin();
    }

    void SpriteBatch::end() {
        for (auto r: renderingQueue) {
            r->draw(graphicsDevice);
            r->active = false;
        }
        graphicsDevice->end();
    }

    void SpriteBatch::setClearColor(const Adagio::Color &color) {
        graphicsDevice->setClearColor(color);
    }

    SpriteState *SpriteBatch::draw(Texture2D &texture, const Vector2d &pos,
                                   short int zIndex) {
        auto *sprite = new(spritePool.getNext()) SpriteState(texture, pos, zIndex);
        sprite->active = true;
        addToRenderingQueue(static_cast<RenderState *>(sprite));
        return sprite;
    }

    TextState *SpriteBatch::drawText(const char *text, const Vector2d &pos,
                                     short int zIndex) {
        auto *txt = new(textPool.getNext()) TextState();
        txt->text = text;
        txt->position = pos;
        txt->zIndex = zIndex;
        txt->active = true;
        addToRenderingQueue(static_cast<RenderState *>(txt));
        return txt;
    }

    void SpriteBatch::addToRenderingQueue(RenderState *r) {
        // TODO: use std::priority_queue instead
        auto it = std::upper_bound(
                renderingQueue.begin(), renderingQueue.end(), r,
                [](RenderState *left, RenderState *right) { return (*left) < (*right); });
        renderingQueue.insert(it, r);
    }

    GraphicsDevice *SpriteBatch::getGraphicsDevice() { return graphicsDevice; }
} // namespace Adagio
