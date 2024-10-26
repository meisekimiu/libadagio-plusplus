#include <catch2/catch.hpp>
#include "../../../src/literals/HashString.h"
#include "../../../src/graphics/font/FontManager.h"

struct TestFont {
    std::string resourceName;
};

struct TestFontLoader : public Adagio::FontLoader<TestFont> {
    std::pair<TestFont, Adagio::FontMetadata> load(const char *resource) override {
        loadedResources.emplace_back(resource);
        return {{resource},
                {}};
    }

    void unload(TestFont font) override {
        unloadedResources.push_back(font.resourceName);
    }

    std::vector<std::string> loadedResources;
    std::vector<std::string> unloadedResources;
};

TEST_CASE("FontManager", "[font][graphics]") {
    TestFontLoader loader;
    Adagio::FontManager<TestFont> fontManager(&loader);

    SECTION("It can load a font") {
        auto font = fontManager.load("font.ttf");
        REQUIRE_FALSE(loader.loadedResources.empty());
        REQUIRE(loader.loadedResources[0] == "font.ttf");

        SECTION("It can use a font") {
            TestFont realFont = fontManager.useFont(font);
            REQUIRE(realFont.resourceName == "font.ttf");
        }

        SECTION("It can fetch a font by name") {
            auto font2 = fontManager.getFont("font.ttf"_hs);
            REQUIRE(font.handle == font2.handle);
            REQUIRE(font.getSecretId() == font2.getSecretId());
        }

        SECTION("It can unload a font") {
            fontManager.unload(font);
            REQUIRE_FALSE(loader.unloadedResources.empty());
            REQUIRE(loader.unloadedResources[0] == "font.ttf");
        }
    }
}
