#ifndef GL_ADAGIO_SOUNDMODIFIERDEVICE_H
#define GL_ADAGIO_SOUNDMODIFIERDEVICE_H

#include "PlayingSoundHandle.h"

namespace Adagio {
    struct SoundModifierDevice {
        virtual void setPlayingVolume(PlayingSoundHandle handle, float volume) = 0;

        virtual void setPlayingPan(PlayingSoundHandle handle, float pan) = 0;

        virtual void setLooping(PlayingSoundHandle handle, bool loop) = 0;

        virtual void stop(PlayingSoundHandle handle) = 0;
    };
}

#endif //GL_ADAGIO_SOUNDMODIFIERDEVICE_H
