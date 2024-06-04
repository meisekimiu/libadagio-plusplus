#ifndef GL_ADAGIO_RAYLIBTEXTURELOADER_H
#define GL_ADAGIO_RAYLIBTEXTURELOADER_H

#include "RaylibTexture.h"
#include "../../graphics/TextureLoader.h"

class RaylibTextureLoader : public Adagio::TextureLoader<RaylibTexture> {
public:
    std::pair<RaylibTexture, Adagio::TextureDimensions> load(const char *resource) override;

    void unload(RaylibTexture texture) override;
};


#endif //GL_ADAGIO_RAYLIBTEXTURELOADER_H
