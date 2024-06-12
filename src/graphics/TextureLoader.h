#ifndef GL_ADAGIO_TEXTURELOADER_H
#define GL_ADAGIO_TEXTURELOADER_H

#include "../resource/ResourceLibrary.h"
#include "TextureDimensions.h"

namespace Adagio {
template <typename T>
struct TextureLoader : public AssetLoader<T, TextureDimensions> {
  virtual std::pair<T, TextureDimensions> load(const char *resource) = 0;

  virtual void unload(T texture) = 0;
};
} // namespace Adagio

#endif // GL_ADAGIO_TEXTURELOADER_H
