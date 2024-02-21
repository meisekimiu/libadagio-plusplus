#ifndef GL_ADAGIO_AUDIOSERVICE_H
#define GL_ADAGIO_AUDIOSERVICE_H

#include "../resource/ResourceLibrary.h"
#include "AudioDevice.h"
#include "AudioMetadata.h"

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

        void play(Sample sample) {
            audioDevice->playSample(sample, *audioLibrary);
        }

        void play(Stream stream) {
            audioDevice->playStream(stream, *audioLibrary);
        }

    private:
        AudioDevice<SampleType, StreamType> *audioDevice;
        AudioLibrary<SampleType, StreamType> *audioLibrary;
    };
}

#endif //GL_ADAGIO_AUDIOSERVICE_H
