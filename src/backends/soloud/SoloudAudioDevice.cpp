#include "SoloudAudioDevice.h"
#include <iostream>

SoloudAudioDevice::SoloudAudioDevice(SoLoud::Soloud &soloud) : Adagio::AudioDevice<SoLoud::Wav, SoLoud::WavStream>(
        &sampleLoader, &streamLoader), soloud(soloud) {
    soloud.init();
}

Adagio::PlayingSoundHandle SoloudAudioDevice::playSample(const Adagio::Sample &sample) {
    auto &asset = audioLibrary.useSample(sample);
    return static_cast<Adagio::PlayingSoundHandle>(soloud.play(asset));
}

Adagio::PlayingSoundHandle SoloudAudioDevice::playStream(const Adagio::Stream &stream) {
    auto &asset = audioLibrary.useStream(stream);
    return static_cast<Adagio::PlayingSoundHandle>(soloud.play(asset));
}

void SoloudAudioDevice::setLooping(Adagio::PlayingSoundHandle handle, bool loop) {
    soloud.setLooping(handle, loop);
}

void SoloudAudioDevice::setPlayingPan(Adagio::PlayingSoundHandle handle, float pan) {
    soloud.setPan(handle, pan);
}

void SoloudAudioDevice::setPlayingVolume(Adagio::PlayingSoundHandle handle, float volume) {
    soloud.setVolume(handle, volume);
}
