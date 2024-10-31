#ifndef GL_ADAGIO_SOLOUDSAMPLELOADER_H
#define GL_ADAGIO_SOLOUDSAMPLELOADER_H

#include "../../audio/AudioMetadata.h"
#include "../../resource/PointerSafeAssetLoader.h"
#include <soloud/soloud_wav.h>

class SoloudSampleLoader : public Adagio::PointerSafeAssetLoader<SoLoud::Wav, Adagio::AudioMetadata> {
    Adagio::AudioMetadata load(const char *resource, SoLoud::Wav *sample) override;

    void unload(SoLoud::Wav *asset) override;
};


#endif //GL_ADAGIO_SOLOUDSAMPLELOADER_H
