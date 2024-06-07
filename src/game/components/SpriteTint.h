#ifndef GL_ADAGIO_SPRITETINT_H
#define GL_ADAGIO_SPRITETINT_H

#include "../../graphics/Color.h"

struct SpriteTint {
    Adagio::Color tint;
    unsigned char opacity{0xff};
};

#endif //GL_ADAGIO_SPRITETINT_H
