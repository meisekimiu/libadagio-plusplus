#ifndef GL_ADAGIO_AUDIOSERVICE_H
#define GL_ADAGIO_AUDIOSERVICE_H

#include "SoundPlayerDevice.h"
#include "AudioMetadata.h"
#include "PlayingSound.h"
#include "AbstractAudioLibrary.h"

namespace Adagio {

    class AudioService {
    public:
        explicit AudioService(SoundPlayerDevice *audioPlayer);

        PlayingSound play(Sample sample);

        PlayingSound play(Stream stream);

        AbstractAudioLibrary &getAudioLibrary() const;

        void setAudioDevice(SoundPlayerDevice *device);

    private:
        SoundPlayerDevice *audioDevice;
    };
} // namespace Adagio

#endif // GL_ADAGIO_AUDIOSERVICE_H
