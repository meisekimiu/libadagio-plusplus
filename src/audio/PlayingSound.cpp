#include "PlayingSound.h"
#include <stdexcept>

namespace Adagio {
    PlayingSound &PlayingSound::setVolume(float volume) {
        checkAudioDevice();
        audioDevice->setPlayingVolume(handle, volume);
        return *this;
    }

    PlayingSound &PlayingSound::setPan(float pan) {
        checkAudioDevice();
        audioDevice->setPlayingPan(handle, pan);
        return *this;
    }

    PlayingSound &PlayingSound::setLooping(bool loop) {
        checkAudioDevice();
        audioDevice->setLooping(handle, loop);
        return *this;
    }

    void PlayingSound::checkAudioDevice() const {
        if (!audioDevice) {
            throw std::runtime_error("No audio device set for playing sound");
        }
    }
} // Adagio
