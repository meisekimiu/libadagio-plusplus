#ifndef GL_ADAGIO_RENDERSTATE_H
#define GL_ADAGIO_RENDERSTATE_H

#include "GraphicsDevice.h"

namespace Adagio {
struct RenderState {
  signed short int zIndex{0};
  bool active{false};

  virtual void draw(GraphicsDevice *graphicsDevice) const = 0;

  bool operator<(const RenderState &other) const;

  virtual ~RenderState() = default;
};
} // namespace Adagio

#endif // GL_ADAGIO_RENDERSTATE_H
