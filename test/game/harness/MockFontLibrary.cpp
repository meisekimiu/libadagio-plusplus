#include "MockFontLibrary.h"

Adagio::Font MockFontLibrary::load(std::string resource) {
    return Adagio::Font{};
}

Adagio::Font MockFontLibrary::getFont(std::uint32_t resourceName) const {
    return Adagio::Font{};
}

void MockFontLibrary::unload(Adagio::Font texture) {

}
