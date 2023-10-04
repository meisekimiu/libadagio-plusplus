#ifndef GL_ADAGIO_AUDIO_H
#define GL_ADAGIO_AUDIO_H

#include "AudioService.h"

namespace Adagio {
    class Audio {
    public:
        static void reset();

        static void set(AudioService *service);

        static AudioService *get();

    private:
        static AudioService *service;
    };
}

#endif //GL_ADAGIO_AUDIO_H
