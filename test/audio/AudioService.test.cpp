#include <catch2/catch.hpp>
#include <vector>
#include <string>
#include "../../src/audio/Audio.h"
#include "mocks/TestingAudioService.h"

static TestingAudioService service;

void setup() {
    service = TestingAudioService();
    Adagio::Audio::reset();
    Adagio::Audio::set(&service);
}

TEST_CASE("AudioService can initialize", "[audio]") {
    setup();
    Adagio::Audio::get()->initialize();
    REQUIRE(service.getOperations().size() == 1);
    REQUIRE(service.getOperations()[0] == "initialized");
}

TEST_CASE("AudioService can close", "[audio]") {
    setup();
    Adagio::Audio::get()->close();
    REQUIRE(service.getOperations().size() == 1);
    REQUIRE(service.getOperations()[0] == "closed");
}

TEST_CASE("AudioService can load a sample", "[audio]") {
    setup();
    auto sample = Adagio::Audio::get()->loadSample("potato.wav");
    REQUIRE(sample != nullptr);
    Adagio::Audio::get()->freeSample(sample);
}

TEST_CASE("AudioService can load a stream", "[audio]") {
    setup();
    auto stream = Adagio::Audio::get()->loadStream("bridge.mp3");
    REQUIRE(stream != nullptr);
    Adagio::Audio::get()->freeStream(stream);
}
