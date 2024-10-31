#include "EcsNullSoundLoader.h"

void EcsNullSoundLoader::unload(NullSound *asset) {

}

Adagio::AudioMetadata EcsNullSoundLoader::load(const char *resource, NullSound *location) {
    return {1.0};
}
