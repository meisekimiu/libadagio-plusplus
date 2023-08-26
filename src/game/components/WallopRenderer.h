#ifndef GL_ADAGIO_WALLOPRENDERER_H
#define GL_ADAGIO_WALLOPRENDERER_H

#include "raylib.h"

struct WallopRenderer {
    Texture2D *texture;
    unsigned char frame;
    float lastFrame;
};

#endif //GL_ADAGIO_WALLOPRENDERER_H
