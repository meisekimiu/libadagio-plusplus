#include <catch2/catch.hpp>
#include "../../src/audio/AudioDevice.h"
#include "../../src/audio/AudioService.h"
#include "../../src/audio/AudioLibrary.h"

struct TestingSample {
    std::string filename;
};

struct TestingStream {
    std::string filename;
};

class TestingAudioDevice : public Adagio::AudioDevice<TestingSample, TestingStream> {
public:
    std::vector<std::string> playedSamples;
    std::vector<std::string> playedStreams;

    void playSample(const Adagio::Sample &sample,
                    Adagio::AudioLibrary<TestingSample, TestingStream> &audioLibrary) override {
        playedSamples.push_back(audioLibrary.useSample(sample).filename);
    }

    void playStream(const Adagio::Stream &stream,
                    Adagio::AudioLibrary<TestingSample, TestingStream> &audioLibrary) override {
        playedStreams.push_back(audioLibrary.useStream(stream).filename);
    }
};

struct TestingSampleLoader : public Adagio::AssetLoader<TestingSample, Adagio::AudioMetadata> {
    std::pair<TestingSample, Adagio::AudioMetadata> load(const char *resource) override {
        return std::make_pair(TestingSample{resource}, Adagio::AudioMetadata{1.0});
    }

    void unload(TestingSample asset) override {}
};

struct TestingStreamLoader : public Adagio::AssetLoader<TestingStream, Adagio::AudioMetadata> {
    std::pair<TestingStream, Adagio::AudioMetadata> load(const char *resource) override {
        return std::make_pair(TestingStream{resource}, Adagio::AudioMetadata{1.0});
    }

    void unload(TestingStream asset) override {}
};

TEST_CASE("AudioService", "[audio]") {
    TestingAudioDevice audioDevice;
    TestingSampleLoader sampleLoader;
    TestingStreamLoader streamLoader;
    Adagio::AudioLibrary<TestingSample, TestingStream> audioLibrary(&sampleLoader, &streamLoader);
    Adagio::AudioService<TestingSample, TestingStream> service(&audioDevice, &audioLibrary);

    SECTION("AudioLibrary can load in a sample") {
        REQUIRE(audioDevice.playedSamples.empty());
        Adagio::Sample sample = audioLibrary.loadSample("oof.wav");

        SECTION("AudioService can play it") {
            service.play(sample);
            REQUIRE(audioDevice.playedSamples.size() == 1);
            REQUIRE(audioDevice.playedSamples[0] == "oof.wav");
        }
    }

    SECTION("AudioLibrary can load in a stream") {
        REQUIRE(audioDevice.playedStreams.empty());
        Adagio::Stream stream = audioLibrary.loadStream("doopeetime.ogg");

        SECTION("AudioService can play it") {
            service.play(stream);
            REQUIRE(audioDevice.playedStreams.size() == 1);
            REQUIRE(audioDevice.playedStreams[0] == "doopeetime.ogg");
        }
    }
}
