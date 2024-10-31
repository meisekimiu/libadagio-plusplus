#ifndef GL_ADAGIO_POINTERSAFERESOURCELIBRARY_H
#define GL_ADAGIO_POINTERSAFERESOURCELIBRARY_H

#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "../literals/HashString.h"
#include "InternalAssetWithSecret.h"
#include "Asset.h"
#include "PointerSafeAssetLoader.h"

namespace Adagio {
    template<typename InternalAssetType, typename MetadataType, typename HandleType, int AllocationSize>
    class PointerSafeResourceLibrary {
    public:
        typedef Asset<HandleType, MetadataType> ResourceType;

        explicit PointerSafeResourceLibrary(PointerSafeAssetLoader<InternalAssetType, MetadataType> &assetLoader) :
                loader(assetLoader) {
            allocatedSlots.reserve(AllocationSize);
            std::fill(allocatedSlots.begin(), allocatedSlots.end(), false);
        }

        ResourceType load(const std::string &load) {
            std::uint32_t resourceName = Adagio::crc(load.c_str(), load.length());
            try {
                return getResource(resourceName);
            } catch (...) {
                auto it = std::find(allocatedSlots.begin(), allocatedSlots.end(), false);
                int offset = it - allocatedSlots.begin();
                auto &asset = assets[offset];
                asset.secret = nextSecret++;
                asset.metadata = loader.load(load.c_str(), &asset.asset);
                allocatedSlots[offset] = true;
                nameMap[Adagio::crc(load.c_str(), load.size())] = offset;
                return Asset<HandleType, MetadataType>{offset, asset.secret, asset.metadata};
            }
        }

        void unload(const ResourceType &resource) {
            auto it = std::find_if(nameMap.begin(), nameMap.end(),
                                   [resource](const std::pair<std::uint32_t, HandleType> &pair) {
                                       return pair.second == resource.handle;
                                   });
            if (it != nameMap.end()) {
                nameMap.erase(it);
            }
            auto &asset = assets[resource.handle];
            loader.unload(&asset.asset);
            asset.secret = 0;
            allocatedSlots[resource.handle] = false;
        }

        InternalAssetType &useResource(const ResourceType &resource) {
            auto &asset = assets[resource.handle];
            if (asset.secret != resource.getSecretId()) {
                throw std::invalid_argument("Unloaded asset used.");
            }
            return asset.asset;
        }

        ResourceType getResource(std::uint32_t name) const {
            auto it = nameMap.find(name);
            if (it != nameMap.end()) {
                HandleType handle = it->second;
                auto &internalAsset = assets[handle];
                return Asset<HandleType, MetadataType>(handle, internalAsset.secret,
                                                       internalAsset.metadata);
            }
            throw std::runtime_error("Resource with id not defined");
        }

    private:
        InternalAssetWithSecret<InternalAssetType, MetadataType, HandleType> assets[AllocationSize];
        PointerSafeAssetLoader<InternalAssetType, MetadataType> &loader;
        std::unordered_map<std::uint32_t, HandleType> nameMap;
        std::vector<bool> allocatedSlots;
        HandleType nextSecret{0};
    };
}

#endif //GL_ADAGIO_POINTERSAFERESOURCELIBRARY_H
