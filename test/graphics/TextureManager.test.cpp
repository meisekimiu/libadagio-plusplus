#include <catch2/catch.hpp>
#include <string>
#include "../../src/graphics/TextureManager.h"
#include "../../src/graphics/TextureLoader.h"

struct TestingTexture {
    int id;
    std::string filename;
};

struct TestingTextureLoader : public Adagio::TextureLoader<TestingTexture> {
    std::pair<TestingTexture, Adagio::TextureDimensions> load(const char *resource) override {
        TestingTexture t{1, resource};
        Adagio::TextureDimensions dim{640, 480};
        return std::make_pair(t, dim);
    }

    void unload(TestingTexture texture) override {
    }
};

TEST_CASE("TextureManager exists", "[TextureManager]") {
    TestingTextureLoader loader;
    Adagio::TextureManager<TestingTexture> texman(&loader);

    SECTION("TextureManager can load textures") {
        auto tex = texman.load("potato.jpg");
        REQUIRE(tex.getWidth() == 640);
        REQUIRE(tex.getHeight() == 480);
    }
}

TEST_CASE("TextureManager loads different handles for textures", "[TextureManager]") {
    TestingTextureLoader loader;
    Adagio::TextureManager<TestingTexture> texman(&loader);

    auto tex = texman.load("potato.jpg");
    auto tex2 = texman.load("leona.png");
    REQUIRE(tex.handle != tex2.handle);
    REQUIRE(tex.getSecretId() != tex2.getSecretId());
}

TEST_CASE("TextureManager will reuse handles when a texture is unloaded", "[TextureManager]") {
    TestingTextureLoader loader;
    Adagio::TextureManager<TestingTexture> texman(&loader);

    auto tex = texman.load("potato.jpg");
    texman.unload(tex);
    auto tex2 = texman.load("leona.png");
    REQUIRE(tex.handle == tex2.handle);
    REQUIRE(tex.getSecretId() != tex2.getSecretId());
}

TEST_CASE("TextureManager will keep higher handles intact when a texture is unloaded", "[TextureManager]") {
    TestingTextureLoader loader;
    Adagio::TextureManager<TestingTexture> texman(&loader);

    auto tex = texman.load("potato.jpg");
    auto tex2 = texman.load("leona.png");
    texman.unload(tex);
    auto tex3 = texman.load("dorothy.png");
    REQUIRE(tex2.handle != tex3.handle);
    REQUIRE(tex.getSecretId() != tex2.getSecretId());
    REQUIRE(tex2.getSecretId() != tex3.getSecretId());
    REQUIRE(tex.getSecretId() != tex3.getSecretId());
}

TEST_CASE("TextureManager can fetch internal data from the texture library", "[TextureManager]") {
    TestingTextureLoader loader;
    Adagio::TextureManager<TestingTexture> texman(&loader);

    auto tex = texman.load("potato.jpg");
    auto internalTex = texman.useTexture(tex);
    REQUIRE(internalTex.filename == "potato.jpg");
}

TEST_CASE("TextureManager will detect if the user is fetching an invalid texture", "[TextureManager]") {
    TestingTextureLoader loader;
    Adagio::TextureManager<TestingTexture> texman(&loader);

    auto tex = texman.load("potato.jpg");
    texman.unload(tex);
    texman.load("tomato.jpg");
    REQUIRE_THROWS(texman.useTexture(tex));
}

TEST_CASE("TextureManager can detect if same texture is loaded twice and reuse the same resource", "[TextureManager]") {
    TestingTextureLoader loader;
    Adagio::TextureManager<TestingTexture> texman(&loader);

    auto tex = texman.load("potato.jpg");
    auto tex2 = texman.load("potato.jpg");
    REQUIRE(tex.handle == tex2.handle);
    REQUIRE(tex.getSecretId() == tex2.getSecretId());
}

TEST_CASE("TextureManager will free up resource names when unloading textures", "[TextureManager]") {
    TestingTextureLoader loader;
    Adagio::TextureManager<TestingTexture> texman(&loader);

    auto tex = texman.load("potato.jpg");
    texman.unload(tex);
    texman.load("tomato.jpg");
    auto tex3 = texman.load("potato.jpg");
    REQUIRE(tex.handle != tex3.handle);
    REQUIRE(tex.getSecretId() != tex3.getSecretId());
}
