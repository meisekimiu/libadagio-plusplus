#ifndef GL_ADAGIO_GAMESERVICES_H
#define GL_ADAGIO_GAMESERVICES_H

#include "../animation/SpriteAnimationLibrary.h"
#include "../input/InputService.h"
#include "../event/MessageDispatchService.h"
#include "../graphics/AbstractTextureManager.h"
#include "GameStats.h"

namespace Adagio {
    struct GameServices {
        struct ResourceLibraryCollection {
            const AbstractTextureManager *textureManager{nullptr};
            SpriteAnimationLibrary *animationLibrary{nullptr};
        };

        MessageDispatchService *messageDispatchService{nullptr};
        GameStats *stats{nullptr};
        ResourceLibraryCollection resources;
        const InputService *input{nullptr};
    };
}

#endif //GL_ADAGIO_GAMESERVICES_H
