#ifndef GL_ADAGIO_ASSETLOADER_H
#define GL_ADAGIO_ASSETLOADER_H

#include <utility>

namespace Adagio {
    template<typename InternalAssetType, typename MetadataType>
    struct AssetLoader {
        virtual std::pair<InternalAssetType, MetadataType> load(const char *resource) = 0;

        virtual void unload(InternalAssetType asset) = 0;
    };
}

#endif //GL_ADAGIO_ASSETLOADER_H
