#ifndef GL_ADAGIO_RENDERSTATE_H
#define GL_ADAGIO_RENDERSTATE_H

namespace Adagio {
    struct RenderState {
        signed short int zIndex{0};
        bool active{false};

        virtual void draw() const = 0;

        bool operator<(const RenderState &other);
    };
}


#endif //GL_ADAGIO_RENDERSTATE_H
