#ifndef GL_ADAGIO_TEXTURE2D_H
#define GL_ADAGIO_TEXTURE2D_H

#include "../resource/Asset.h"
#include "TextureDimensions.h"

namespace Adagio {
typedef unsigned int TextureHandle;

class Texture2D : public Asset<TextureHandle, TextureDimensions> {
public:
  Texture2D();

  explicit Texture2D(TextureHandle handle, TextureHandle secret,
                     unsigned int width, unsigned int height);

  unsigned int getWidth();

  unsigned int getHeight();
};
} // namespace Adagio
#endif // GL_ADAGIO_TEXTURE2D_H
