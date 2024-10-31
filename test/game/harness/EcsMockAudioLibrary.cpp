#include "EcsMockAudioLibrary.h"

Adagio::Sample EcsMockAudioLibrary::loadSample(const std::string &resource) {
    return Adagio::Sample{Adagio::Asset<Adagio::AudioHandle, Adagio::AudioMetadata>{1, 1, {1.0}}};
}

Adagio::Stream EcsMockAudioLibrary::loadStream(const std::string &resource) {
    return Adagio::Stream{Adagio::Asset<Adagio::AudioHandle, Adagio::AudioMetadata>{1, 1, {1.0}}};
}

NullSound &EcsMockAudioLibrary::useSample(const Adagio::Sample &sample) {
    return sound;
}

NullSound &EcsMockAudioLibrary::useStream(const Adagio::Stream &stream) {
    return sound;
}

Adagio::Sample EcsMockAudioLibrary::getSample(std::uint32_t name) {
    return loadSample("potato");
}

Adagio::Stream EcsMockAudioLibrary::getStream(std::uint32_t name) {
    return loadStream("potato");
}

void EcsMockAudioLibrary::unload(Adagio::Sample &sample) {}

void EcsMockAudioLibrary::unload(Adagio::Stream &stream) {}

EcsMockAudioLibrary::EcsMockAudioLibrary() : Adagio::AudioLibrary<NullSound, NullSound>(loader, loader) {}
