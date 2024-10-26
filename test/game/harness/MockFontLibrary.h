#ifndef GL_ADAGIO_MOCKFONTLIBRARY_H
#define GL_ADAGIO_MOCKFONTLIBRARY_H

#include "../../../src/graphics/font/AbstractFontManager.h"

class MockFontLibrary : public Adagio::AbstractFontManager {
    Adagio::Font load(std::string resource) override;

    Adagio::Font getFont(std::uint32_t resourceName) const override;

    void unload(Adagio::Font texture) override;
};


#endif //GL_ADAGIO_MOCKFONTLIBRARY_H
