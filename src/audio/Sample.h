#ifndef GL_ADAGIO_SAMPLE_H
#define GL_ADAGIO_SAMPLE_H

#include "../resource/Asset.h"
#include "AudioMetadata.h"

namespace Adagio {
struct Sample : public Asset<AudioHandle, AudioMetadata> {
  Sample();

  explicit Sample(const Asset<AudioHandle, AudioMetadata> &&asset)
      : Asset(asset.handle, asset.getSecretId(), asset.getMetadata()) {}
};
} // namespace Adagio

#endif // GL_ADAGIO_SAMPLE_H
