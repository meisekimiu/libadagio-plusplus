#include "AudioService.h"

namespace Adagio {
    AudioService::AudioService(SoundPlayerDevice *audioPlayer) {
        audioDevice = audioPlayer;
    }

    PlayingSound AudioService::play(Sample sample) {
        PlayingSoundHandle handle = audioDevice->playSample(sample);
        return PlayingSound{handle, audioDevice};
    }

    PlayingSound AudioService::play(Stream stream) {
        PlayingSoundHandle handle = audioDevice->playStream(stream);
        return PlayingSound{handle, audioDevice};
    }

    AbstractAudioLibrary &AudioService::getAudioLibrary() const {
        return audioDevice->getAudioLibrary();
    }

    void AudioService::setAudioDevice(SoundPlayerDevice *device) {
        audioDevice = device;
    }

    void AudioService::stopAll() {
        audioDevice->stopAll();
    }
    }
