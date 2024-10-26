#ifndef GL_ADAGIO_FONTMANAGER_H
#define GL_ADAGIO_FONTMANAGER_H

#include "../../resource/ResourceLibrary.h"
#include "AbstractFontManager.h"
#include "Font.h"
#include "FontLoader.h"

namespace Adagio {
    template<typename T>
    class FontManager : public AbstractFontManager {
    public:
        explicit FontManager(FontLoader<T> *loader);

        Font load(std::string path) override;

        void unload(Font font) override;

        T useFont(Font font) const;

        [[nodiscard]] Font getFont(std::uint32_t name) const override;

    private:
        ResourceLibrary<T, FontMetadata, FontHandle> library;
    };

#include "FontManager-impl.h"

}

#endif //GL_ADAGIO_FONTMANAGER_H
