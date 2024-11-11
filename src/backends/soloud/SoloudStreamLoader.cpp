#include "SoLoudStreamLoader.h"

Adagio::AudioMetadata SoloudStreamLoader::load(const char *resource,
                                               SoLoud::WavStream *stream) {
  stream->load(resource);
  return {stream->getLength()};
}

void SoloudStreamLoader::unload(SoLoud::WavStream *asset) {
  // Simply freeing the struct is good enough!
}
