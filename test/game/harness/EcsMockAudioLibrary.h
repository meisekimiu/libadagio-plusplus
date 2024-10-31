#ifndef GL_ADAGIO_ECSMOCKAUDIOLIBRARY_H
#define GL_ADAGIO_ECSMOCKAUDIOLIBRARY_H

#include "../../../src/audio/AudioLibrary.h"
#include "NullSound.h"
#include "EcsNullSoundLoader.h"

class EcsMockAudioLibrary : public Adagio::AudioLibrary<NullSound, NullSound> {
public:
    NullSound sound;

    EcsMockAudioLibrary();

    Adagio::Sample loadSample(const std::string &resource) override;

    Adagio::Stream loadStream(const std::string &resource) override;

    NullSound &useSample(const Adagio::Sample &sample) override;

    NullSound &useStream(const Adagio::Stream &stream) override;

    Adagio::Sample getSample(std::uint32_t name) override;

    Adagio::Stream getStream(std::uint32_t name) override;

    void unload(Adagio::Sample &sample) override;

    void unload(Adagio::Stream &stream) override;

private:
    EcsNullSoundLoader loader;
};


#endif //GL_ADAGIO_ECSMOCKAUDIOLIBRARY_H
