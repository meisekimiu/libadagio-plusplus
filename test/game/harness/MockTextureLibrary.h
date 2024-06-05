#ifndef GL_ADAGIO_MOCKTEXTURELIBRARY_H
#define GL_ADAGIO_MOCKTEXTURELIBRARY_H

#include "../../../src/graphics/AbstractTextureManager.h"

class MockTextureLibrary : public Adagio::AbstractTextureManager {
public:
    Adagio::Texture2D load(std::string resource) override;

    void unload(Adagio::Texture2D texture) override;
};

#endif //GL_ADAGIO_MOCKTEXTURELIBRARY_H
