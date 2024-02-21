#ifndef GL_ADAGIO_STREAM_H
#define GL_ADAGIO_STREAM_H

#include "../resource/Asset.h"
#include "AudioMetadata.h"

namespace Adagio {
    struct Stream : public Asset<AudioHandle, AudioMetadata> {
        Stream(Asset<AudioHandle, AudioMetadata> &&asset) : Asset<AudioHandle, AudioMetadata>(asset.handle,
                                                                                              asset.getSecretId(),
                                                                                              asset.getMetadata()) {}
    };
}

#endif //GL_ADAGIO_STREAM_H
