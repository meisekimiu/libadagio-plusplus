#include <catch2/catch.hpp>
#include "../../src/audio/Audio.h"
#include "mocks/TestingAudioService.h"

TEST_CASE("Audio can reset", "[audio]") {
    TestingAudioService s;
    Adagio::Audio::set(&s);
    Adagio::Audio::reset();
    REQUIRE(Adagio::Audio::get() != &s);
}

TEST_CASE("Audio can set AudioService", "[audio]") {
    TestingAudioService s;
    Adagio::Audio::set(&s);

    SECTION("It does not allow null values", "[audio]") {
        REQUIRE_THROWS(Adagio::Audio::set(nullptr));
    }
}

TEST_CASE("Audio can get AudioService", "[audio]") {
    TestingAudioService s;
    Adagio::Audio::set(&s);
    REQUIRE(Adagio::Audio::get() == &s);
}
