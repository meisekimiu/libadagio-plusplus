#ifndef GL_ADAGIO_RAYLIBFONTLOADER_H
#define GL_ADAGIO_RAYLIBFONTLOADER_H

#include "../../graphics/font/FontLoader.h"
#include "RaylibFont.h"

struct RaylibFontLoader : public Adagio::FontLoader<RaylibFont> {
    std::pair<RaylibFont, Adagio::FontMetadata> load(const char *resource) override;

    void unload(RaylibFont font) override;
};


#endif //GL_ADAGIO_RAYLIBFONTLOADER_H
