#ifndef GL_ADAGIO_SOLOUDSTREAMLOADER_H
#define GL_ADAGIO_SOLOUDSTREAMLOADER_H

#include "../../audio/AudioMetadata.h"
#include "../../resource/PointerSafeAssetLoader.h"
#include <soloud_wavstream.h>

class SoloudStreamLoader
    : public Adagio::PointerSafeAssetLoader<SoLoud::WavStream,
                                            Adagio::AudioMetadata> {
  Adagio::AudioMetadata load(const char *resource,
                             SoLoud::WavStream *stream) override;

  void unload(SoLoud::WavStream *asset) override;
};

#endif // GL_ADAGIO_SOLOUDSTREAMLOADER_H
