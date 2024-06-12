#ifndef GL_ADAGIO_ASSET_H
#define GL_ADAGIO_ASSET_H

namespace Adagio {
template <typename HandleType, typename MetadataType> class Asset {
public:
  explicit Asset(HandleType handle, HandleType secret,
                 const MetadataType &metadata) {
    this->handle = handle;
    this->secret = secret;
    this->metadata = metadata;
  }

  HandleType handle;

  HandleType getSecretId() const { return secret; }

  [[nodiscard]] bool isValid() const { return secret != 0; }

  MetadataType getMetadata() const { return metadata; }

protected:
  HandleType secret;
  MetadataType metadata;
};
} // namespace Adagio

#endif // GL_ADAGIO_ASSET_H
