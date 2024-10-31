#ifndef GL_ADAGIO_SOUNDPLAYERDEVICE_H
#define GL_ADAGIO_SOUNDPLAYERDEVICE_H

#include "PlayingSoundHandle.h"
#include "SoundModifierDevice.h"
#include "Sample.h"
#include "Stream.h"
#include "AbstractAudioLibrary.h"

namespace Adagio {
    struct SoundPlayerDevice : public SoundModifierDevice {
        virtual PlayingSoundHandle playSample(const Sample &sample) = 0;

        virtual PlayingSoundHandle playStream(const Stream &stream) = 0;

        virtual AbstractAudioLibrary &getAudioLibrary() = 0;
    };
}

#endif //GL_ADAGIO_SOUNDPLAYERDEVICE_H
