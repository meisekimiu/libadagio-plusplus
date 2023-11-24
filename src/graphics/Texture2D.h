#ifndef GL_ADAGIO_TEXTURE2D_H
#define GL_ADAGIO_TEXTURE2D_H
namespace Adagio {
    typedef unsigned int TextureHandle;

    class Texture2D {
    public:
        explicit Texture2D(TextureHandle handle, TextureHandle secret, unsigned int width, unsigned int height);

        TextureHandle handle;

        unsigned int getWidth();

        unsigned int getHeight();

        TextureHandle getSecretId();

        bool isValid();

    private:
        TextureHandle secret;
        unsigned int width;
        unsigned int height;
    };
}
#endif //GL_ADAGIO_TEXTURE2D_H
