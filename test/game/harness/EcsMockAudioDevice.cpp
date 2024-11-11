#include "EcsMockAudioDevice.h"

EcsMockAudioDevice::EcsMockAudioDevice()
    : Adagio::AudioDevice<NullSound, NullSound>(&loader, &loader) {}

Adagio::PlayingSoundHandle
EcsMockAudioDevice::playSample(const Adagio::Sample &sample) {
  return 0;
}

Adagio::PlayingSoundHandle
EcsMockAudioDevice::playStream(const Adagio::Stream &stream) {
  return 0;
}

void EcsMockAudioDevice::setPlayingVolume(Adagio::PlayingSoundHandle handle,
                                          float volume) {}

void EcsMockAudioDevice::setPlayingPan(Adagio::PlayingSoundHandle handle,
                                       float pan) {}

void EcsMockAudioDevice::setLooping(Adagio::PlayingSoundHandle handle,
                                    bool loop) {}

Adagio::AbstractAudioLibrary &EcsMockAudioDevice::getAudioLibrary() {
  return mockLibrary;
}

void EcsMockAudioDevice::stopAll() {}

void EcsMockAudioDevice::stop(Adagio::PlayingSoundHandle handle) {}
