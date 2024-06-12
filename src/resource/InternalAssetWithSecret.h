#ifndef GL_ADAGIO_INTERNALASSETWITHSECRET_H
#define GL_ADAGIO_INTERNALASSETWITHSECRET_H

namespace Adagio {
template <typename InternalAssetType, typename MetadataType,
          typename HandleType>
struct InternalAssetWithSecret {
  HandleType secret;
  MetadataType metadata;
  InternalAssetType asset;
};
} // namespace Adagio

#endif // GL_ADAGIO_INTERNALASSETWITHSECRET_H
