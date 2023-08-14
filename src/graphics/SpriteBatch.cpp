#include "SpriteBatch.h"
#include <raylib.h>
#include <algorithm>

namespace Adagio {
    SpriteBatch::SpriteBatch() {
        renderingQueue.reserve(64);
    }

    void SpriteBatch::begin() {
        BeginDrawing();
        renderingQueue.clear();
        ClearBackground(clearColor);
        spritePool.begin();
        textPool.begin();
    }

    void SpriteBatch::end() {
        for (auto r: renderingQueue) {
            r->draw();
            r->active = false;
        }
        EndDrawing();
    }

    SpriteState *SpriteBatch::draw(Texture2D &texture, const Vector2 &pos, short int zIndex) {
        auto *sprite = new(spritePool.getNext()) SpriteState(texture, pos, zIndex);
        sprite->active = true;
        addToRenderingQueue(static_cast<RenderState *>(sprite));
        return sprite;
    }

    TextState *SpriteBatch::drawText(const char *text, const Vector2 &pos, short int zIndex) {
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
        auto it = std::upper_bound(renderingQueue.begin(), renderingQueue.end(), r,
                                   [](RenderState *left, RenderState *right) {
                                       return (*left) < (*right);
                                   });
        renderingQueue.insert(it, r);
    }
} // Adagio
