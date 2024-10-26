#include "RaylibFontLoader.h"
#include <iostream>

std::pair<RaylibFont, Adagio::FontMetadata> RaylibFontLoader::load(const char *resource) {
    Font font = LoadFont(resource);
    return {font, {font.baseSize}};
}

void RaylibFontLoader::unload(RaylibFont font) {
    UnloadFont(font);
}


