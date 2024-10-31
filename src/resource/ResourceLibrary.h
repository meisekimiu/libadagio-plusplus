#ifndef GL_ADAGIO_RESOURCELIBRARY_H
#define GL_ADAGIO_RESOURCELIBRARY_H

#include "../literals/HashString.h"
#include "Asset.h"
#include "AssetLoader.h"
#include "InternalAssetWithSecret.h"
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

namespace Adagio {
    template<typename InternalAssetType, typename MetadataType,
            typename HandleType>
    class ResourceLibrary {
        typedef Asset<HandleType, MetadataType> ResourceType;
        typedef InternalAssetWithSecret<InternalAssetType, MetadataType, HandleType>
                ResourceWithSecret;
        typedef AssetLoader<InternalAssetType, MetadataType> LoaderType;

    public:
        explicit ResourceLibrary(
                AssetLoader<InternalAssetType, MetadataType> *loader) {
            this->loader = loader;
            library.reserve(64);
            nextSecret = 1;
        }

        ResourceType load(const std::string &resource) {
            std::uint32_t resourceName = Adagio::crc(resource.c_str(), resource.length());
            try {
                return getResource(resourceName);
            } catch (...) {
                auto internalTexture = loader->load(resource.c_str());
                auto dimensions = internalTexture.second;
                HandleType secret = nextSecret++;
                HandleType id;
                if (!freeHandles.empty()) {
                    id = freeHandles.back();
                    freeHandles.pop_back();
                    library[id - 1] = {secret, dimensions, internalTexture.first};
                } else {
                    id = library.size() + 1;
                    library.push_back({secret, dimensions, internalTexture.first});
                }
                loadedHashes[resourceName] = id;
                Asset<HandleType, MetadataType> handle(id, secret, dimensions);
                return handle;
            }
        }

        void unload(const ResourceType &asset) {
            ResourceWithSecret internalTexture = library[asset.handle - 1];
            internalTexture.secret = 0;
            loader->unload(internalTexture.asset);
            freeHandles.push_back(asset.handle);
            for (auto it = loadedHashes.begin(); it != loadedHashes.end(); it++) {
                if (it->second == asset.handle) {
                    loadedHashes.erase(it);
                    break;
                }
            }
        }

        InternalAssetType &useResource(const ResourceType &asset) {
            ResourceWithSecret &internalTexture = library[asset.handle - 1];
            if (asset.getSecretId() != internalTexture.secret) {
                throw std::invalid_argument("Unloaded texture used.");
            }
            return internalTexture.asset;
        }

        ResourceType getResource(std::uint32_t resourceName) const {
            if (loadedHashes.find(resourceName) != loadedHashes.end()) {
                HandleType handle = loadedHashes[resourceName] - 1;
                ResourceWithSecret internalAsset = library[handle];
                return Asset<HandleType, MetadataType>(handle + 1, internalAsset.secret,
                                                       internalAsset.metadata);
            }
            throw std::runtime_error("Resource with id not defined");
        }

    private:
        AssetLoader<InternalAssetType, MetadataType> *loader;
        std::vector<ResourceWithSecret> library;
        std::vector<HandleType> freeHandles;
        mutable std::unordered_map<std::uint32_t, HandleType> loadedHashes;

        HandleType nextSecret;
    };
} // namespace Adagio
#endif // GL_ADAGIO_RESOURCELIBRARY_H
