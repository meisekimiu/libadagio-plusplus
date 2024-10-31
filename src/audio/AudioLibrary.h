#ifndef GL_ADAGIO_AUDIOLIBRARY_H
#define GL_ADAGIO_AUDIOLIBRARY_H

#include "AbstractAudioLibrary.h"
#include "AudioMetadata.h"
#include "Sample.h"
#include "Stream.h"
#include "../resource/PointerSafeResourceLibrary.h"

#define MAX_SAMPLES 64
#define MAX_STREAMS 16

namespace Adagio {
    template<class SampleType, class StreamType>
    class AudioLibrary : public AbstractAudioLibrary {
    public:
        explicit AudioLibrary(PointerSafeAssetLoader<SampleType, AudioMetadata> &sampleLoader,
                              PointerSafeAssetLoader<StreamType, AudioMetadata> &streamLoader)
                : sampleLibrary(sampleLoader), streamLibrary(streamLoader) {}

        Sample loadSample(const std::string &resource) override {
            return Sample(sampleLibrary.load(resource));
        }

        virtual SampleType &useSample(const Sample &sample) {
            return sampleLibrary.useResource(sample);
        }

        Sample getSample(std::uint32_t name) override {
            return Sample(sampleLibrary.getResource(name));
        }

        Stream loadStream(const std::string &resource) override {
            return Stream(streamLibrary.load(resource));
        }

        virtual StreamType &useStream(const Stream &stream) {
            return streamLibrary.useResource(stream);
        }

        Stream getStream(std::uint32_t name) override {
            return Stream(streamLibrary.getResource(name));
        }

        void unload(Sample &sample) override { sampleLibrary.unload(sample); }

        void unload(Stream &stream) override { streamLibrary.unload(stream); }

    private:
        PointerSafeResourceLibrary<SampleType, AudioMetadata, AudioHandle, MAX_SAMPLES> sampleLibrary;
        PointerSafeResourceLibrary<StreamType, AudioMetadata, AudioHandle, MAX_STREAMS> streamLibrary;
    };
} // namespace Adagio

#endif // GL_ADAGIO_AUDIOLIBRARY_H
