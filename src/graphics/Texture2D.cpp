#include "Texture2D.h"

Adagio::Texture2D::Texture2D(Adagio::TextureHandle handle,
                             Adagio::TextureHandle secret,
                             unsigned int width,
                             unsigned int height) {
    this->handle = handle;
    this->secret = secret;
    this->width = width;
    this->height = height;
}

unsigned int Adagio::Texture2D::getHeight() {
    return height;
}

unsigned int Adagio::Texture2D::getWidth() {
    return width;
}

Adagio::TextureHandle Adagio::Texture2D::getSecretId() {
    return secret;
}

bool Adagio::Texture2D::isValid() {
    return handle != 0;
}
