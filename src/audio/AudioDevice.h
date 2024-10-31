#ifndef GL_ADAGIO_AUDIODEVICE_H
#define GL_ADAGIO_AUDIODEVICE_H

#include "AudioLibrary.h"
#include "Sample.h"
#include "Stream.h"
#include "SoundModifierDevice.h"
#include "SoundPlayerDevice.h"

namespace Adagio {
    template<class SampleType, class StreamType>
    class AudioDevice : public SoundPlayerDevice {
    public:
        AudioDevice(PointerSafeAssetLoader<SampleType, AudioMetadata> *sampleLoader,
                    PointerSafeAssetLoader<StreamType, AudioMetadata> *streamLoader);

        AbstractAudioLibrary &getAudioLibrary() override;

    protected:
        AudioLibrary<SampleType, StreamType> audioLibrary;
    };

    template<class SampleType, class StreamType>
    AudioDevice<SampleType, StreamType>::AudioDevice(PointerSafeAssetLoader<SampleType, AudioMetadata> *sampleLoader,
                                                     PointerSafeAssetLoader<StreamType, AudioMetadata> *streamLoader)
            : audioLibrary(*sampleLoader, *streamLoader) {}

    template<class SampleType, class StreamType>
    AbstractAudioLibrary &AudioDevice<SampleType, StreamType>::getAudioLibrary() {
        return audioLibrary;
    }
} // namespace Adagio

#endif // GL_ADAGIO_AUDIODEVICE_H
