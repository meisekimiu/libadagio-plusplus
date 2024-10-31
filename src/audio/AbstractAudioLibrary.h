#ifndef GL_ADAGIO_ABSTRACTAUDIOLIBRARY_H
#define GL_ADAGIO_ABSTRACTAUDIOLIBRARY_H

#include "Sample.h"
#include "Stream.h"
#include <string>
#include <cstdint>

namespace Adagio {
    struct AbstractAudioLibrary {
        virtual Sample loadSample(const std::string &resource) = 0;

        virtual void unload(Sample &sample) = 0;

        virtual Sample getSample(std::uint32_t name) = 0;

        virtual Stream loadStream(const std::string &resource) = 0;

        virtual void unload(Stream &stream) = 0;

        virtual Stream getStream(std::uint32_t name) = 0;
    };
}

#endif //GL_ADAGIO_ABSTRACTAUDIOLIBRARY_H
