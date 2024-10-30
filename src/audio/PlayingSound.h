#ifndef GL_ADAGIO_PLAYINGSOUND_H
#define GL_ADAGIO_PLAYINGSOUND_H

#include "PlayingSoundHandle.h"
#include "SoundModifierDevice.h"

namespace Adagio {

    class PlayingSound {
    public:
        PlayingSoundHandle handle;
        SoundModifierDevice *audioDevice;

        PlayingSound &setVolume(float volume);

        PlayingSound &setPan(float pan);

        PlayingSound &setLooping(bool loop);

    private:
        void checkAudioDevice() const;
    };

} // Adagio

#endif //GL_ADAGIO_PLAYINGSOUND_H
