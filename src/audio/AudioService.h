#ifndef GL_ADAGIO_AUDIOSERVICE_H
#define GL_ADAGIO_AUDIOSERVICE_H

#include <string>
#include "Sample.h"
#include "Stream.h"

namespace Adagio {
    struct AudioService {
        virtual void initialize() = 0;

        virtual void close() = 0;

        virtual Sample *loadSample(std::string path) = 0;

        virtual Stream *loadStream(std::string path) = 0;

        virtual void freeSample(Sample *sample) = 0;

        virtual void freeStream(Stream *stream) = 0;
    };
}

#endif //GL_ADAGIO_AUDIOSERVICE_H
