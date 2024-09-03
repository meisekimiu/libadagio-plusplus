#ifndef GL_ADAGIO_GAMESERVICES_H
#define GL_ADAGIO_GAMESERVICES_H

#include "../event/MessageDispatchService.h"
#include "../graphics/AbstractTextureManager.h"
#include "GameStats.h"

namespace Adagio {
    struct GameServices {
        struct ResourceLibraryCollection {
            const Adagio::AbstractTextureManager *textureManager{nullptr};
        };

        Adagio::MessageDispatchService *messageDispatchService{nullptr};
        Adagio::GameStats *stats{nullptr};
        ResourceLibraryCollection resources;
    };
}

#endif //GL_ADAGIO_GAMESERVICES_H
