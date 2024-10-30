#ifndef GL_ADAGIO_AUDIOSERVICE_H
#define GL_ADAGIO_AUDIOSERVICE_H

#include "../resource/ResourceLibrary.h"
#include "AudioDevice.h"
#include "AudioMetadata.h"
#include "PlayingSound.h"

namespace Adagio {
    typedef unsigned int AudioHandle;

    template<class SampleType, class StreamType>
    class AudioService {
    public:
        explicit AudioService(AudioDevice<SampleType, StreamType> *audioPlayer,
                              AudioLibrary<SampleType, StreamType> *audioLibrary) {
            audioDevice = audioPlayer;
            this->audioLibrary = audioLibrary;
        }

        PlayingSound play(Sample sample) {
            PlayingSoundHandle handle = audioDevice->playSample(sample, *audioLibrary);
            return PlayingSound{handle, audioDevice};
        }

        PlayingSound play(Stream stream) {
            PlayingSoundHandle handle = audioDevice->playStream(stream, *audioLibrary);
            return PlayingSound{handle, audioDevice};
        }

    private:
        AudioDevice<SampleType, StreamType> *audioDevice;
        AudioLibrary<SampleType, StreamType> *audioLibrary;
    };
} // namespace Adagio

#endif // GL_ADAGIO_AUDIOSERVICE_H
