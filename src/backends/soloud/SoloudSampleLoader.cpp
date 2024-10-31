#include "SoloudSampleLoader.h"

Adagio::AudioMetadata SoloudSampleLoader::load(const char *resource, SoLoud::Wav *sample) {
    sample->load(resource);
    return {sample->getLength()};
}

void SoloudSampleLoader::unload(SoLoud::Wav *asset) {
    // Simply freeing the struct is good enough?
}
