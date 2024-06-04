#ifndef GL_ADAGIO_ABSTRACTTEXTUREMANAGER_H
#define GL_ADAGIO_ABSTRACTTEXTUREMANAGER_H

#include "Texture2D.h"
#include <string>

namespace Adagio {
    class AbstractTextureManager {
    public:
        virtual Texture2D load(std::string resource) = 0;

        virtual void unload(Texture2D texture) = 0;
    };
}

#endif //GL_ADAGIO_ABSTRACTTEXTUREMANAGER_H
