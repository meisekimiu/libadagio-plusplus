#include "Texture2D.h"

Adagio::Texture2D::Texture2D(Adagio::TextureHandle handle,
                             Adagio::TextureHandle secret,
                             unsigned int width,
                             unsigned int height) : Asset<TextureHandle, TextureDimensions>(
        handle, secret,
        {width, height}) {}

unsigned int Adagio::Texture2D::getHeight() {
    return metadata.height;
}

unsigned int Adagio::Texture2D::getWidth() {
    return metadata.width;
}

Adagio::Texture2D::Texture2D() : Asset<TextureHandle, TextureDimensions>(
        0, 0, {0, 0}) {
}
