#ifndef GL_ADAGIO_POINTERSAFEASSETLOADER_H
#define GL_ADAGIO_POINTERSAFEASSETLOADER_H

#include <utility>

namespace Adagio {
    template<typename InternalAssetType, typename MetadataType>
    struct PointerSafeAssetLoader {
        virtual MetadataType load(const char *resource, InternalAssetType *location) = 0;

        virtual void unload(InternalAssetType *asset) = 0;
    };
} // namespace Adagio

#endif //GL_ADAGIO_POINTERSAFEASSETLOADER_H
