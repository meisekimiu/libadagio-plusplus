#ifndef GL_ADAGIO_TEXTUREMANAGER_H
#define GL_ADAGIO_TEXTUREMANAGER_H

#include "../resource/ResourceLibrary.h"
#include "AbstractTextureManager.h"
#include "Texture2D.h"
#include "TextureLoader.h"
#include <string>

namespace Adagio {
template <typename T> class TextureManager : public AbstractTextureManager {
public:
  explicit TextureManager(TextureLoader<T> *loader);

  Texture2D load(std::string resource) override;

  void unload(Texture2D texture) override;

  T useTexture(Texture2D texture);

private:
  ResourceLibrary<T, TextureDimensions, TextureHandle> library;
};
} // namespace Adagio

#include "TextureManager-impl.h"

#endif // GL_ADAGIO_TEXTUREMANAGER_H
