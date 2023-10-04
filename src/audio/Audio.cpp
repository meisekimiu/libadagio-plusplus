#include "Audio.h"
#include <stdexcept>

namespace Adagio {
    AudioService *Audio::service = nullptr;

    void Audio::reset() {
        service = nullptr;
    }

    void Audio::set(AudioService *s) {
        if (!s) {
            throw std::invalid_argument("AudioService cannot be null");
        }
        service = s;
    }

    AudioService *Audio::get() {
        return service;
    }
}
