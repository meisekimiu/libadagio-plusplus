#ifndef GL_ADAGIO_ECSNULLSOUNDLOADER_H
#define GL_ADAGIO_ECSNULLSOUNDLOADER_H

#include "NullSound.h"
#include "../../../src/audio/AudioMetadata.h"
#include "../../../src/resource/PointerSafeAssetLoader.h"

class EcsNullSoundLoader : public Adagio::PointerSafeAssetLoader<NullSound, Adagio::AudioMetadata> {
    Adagio::AudioMetadata load(const char *resource, NullSound *location) override;

    void unload(NullSound *asset) override;
};


#endif //GL_ADAGIO_ECSNULLSOUNDLOADER_H
