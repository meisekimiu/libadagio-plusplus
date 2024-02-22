#ifndef GL_ADAGIO_AUDIOLIBRARY_H
#define GL_ADAGIO_AUDIOLIBRARY_H

#include "../resource/ResourceLibrary.h"
#include "AudioMetadata.h"
#include "Sample.h"
#include "Stream.h"

namespace Adagio {
    template<class SampleType, class StreamType>
    class AudioLibrary {
    public:
        explicit AudioLibrary(AssetLoader<SampleType, AudioMetadata> *sampleLoader,
                              AssetLoader<StreamType, AudioMetadata> *streamLoader) : sampleLibrary(sampleLoader),
                                                                                      streamLibrary(streamLoader) {
        }

        Sample loadSample(const std::string &resource) {
            return Sample(sampleLibrary.load(resource));
        }

        SampleType useSample(const Sample &sample) {
            return sampleLibrary.useResource(sample);
        }

        Stream loadStream(const std::string &resource) {
            return Stream(streamLibrary.load(resource));
        }

        StreamType useStream(const Stream &stream) {
            return streamLibrary.useResource(stream);
        }

        void unload(Sample &sample) {
            sampleLibrary.unload(sample);
        }

        void unload(Stream &stream) {
            streamLibrary.unload(stream);
        }

    private:
        ResourceLibrary<SampleType, AudioMetadata, AudioHandle> sampleLibrary;
        ResourceLibrary<StreamType, AudioMetadata, AudioHandle> streamLibrary;
    };
}

#endif //GL_ADAGIO_AUDIOLIBRARY_H
