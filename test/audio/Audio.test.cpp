#include "../../src/audio/AudioDevice.h"
#include "../../src/audio/AudioService.h"
#include <catch2/catch.hpp>

struct TestingSample {
  std::string filename;
};

struct TestingStream {
  std::string filename;
};

struct PlayingSoundData {
  float volume{1};
  float pan{0};
  bool loop{false};
};

struct TestingSampleLoader
    : public Adagio::PointerSafeAssetLoader<TestingSample,
                                            Adagio::AudioMetadata> {
  bool unloaded{false};

  Adagio::AudioMetadata load(const char *resource,
                             TestingSample *sample) override {
    sample->filename = resource;
    return Adagio::AudioMetadata{1.0};
  }

  void unload(TestingSample *asset) override { unloaded = true; }
};

struct TestingStreamLoader
    : public Adagio::PointerSafeAssetLoader<TestingStream,
                                            Adagio::AudioMetadata> {
  bool unloaded{false};

  Adagio::AudioMetadata load(const char *resource,
                             TestingStream *stream) override {
    stream->filename = resource;
    return Adagio::AudioMetadata{1.0};
  }

  void unload(TestingStream *asset) override { unloaded = true; }
};

class TestingAudioDevice
    : public Adagio::AudioDevice<TestingSample, TestingStream> {
public:
  std::vector<std::string> playedSamples;
  std::vector<std::string> playedStreams;
  std::vector<PlayingSoundData> playingSoundData;

  explicit TestingAudioDevice(TestingSampleLoader *sampleLoader,
                              TestingStreamLoader *streamLoader)
      : Adagio::AudioDevice<TestingSample, TestingStream>(sampleLoader,
                                                          streamLoader) {}

  Adagio::PlayingSoundHandle playSample(const Adagio::Sample &sample) override {
    playedSamples.push_back(audioLibrary.useSample(sample).filename);
    playingSoundData.emplace_back();
    return playingSoundData.size() - 1;
  }

  void setPlayingVolume(Adagio::PlayingSoundHandle id, float volume) override {
    playingSoundData[id].volume = volume;
  }

  void setPlayingPan(Adagio::PlayingSoundHandle handle, float pan) override {
    playingSoundData[handle].pan = pan;
  }

  void setLooping(Adagio::PlayingSoundHandle handle, bool loop) override {
    playingSoundData[handle].loop = loop;
  }

  Adagio::PlayingSoundHandle playStream(const Adagio::Stream &stream) override {
    playedStreams.push_back(audioLibrary.useStream(stream).filename);
    playingSoundData.emplace_back();
    return playingSoundData.size() - 1;
  }

  void resetPlayingSounds() { playingSoundData.clear(); }

  void stop(Adagio::PlayingSoundHandle handle) override {}

  void stopAll() override {}
};

TEST_CASE("PlayingSound nulls", "[audio]") {
  Adagio::PlayingSound nullSound{0, nullptr};

  REQUIRE_THROWS(nullSound.setVolume(1));
  REQUIRE_THROWS(nullSound.setPan(0));
  REQUIRE_THROWS(nullSound.setLooping(false));
}

TEST_CASE("AudioService", "[audio]") {
  TestingSampleLoader sampleLoader;
  TestingStreamLoader streamLoader;
  TestingAudioDevice audioDevice(&sampleLoader, &streamLoader);
  Adagio::AudioService service(&audioDevice);
  Adagio::AbstractAudioLibrary &audioLibrary = service.getAudioLibrary();

  SECTION("AudioLibrary can load in a sample") {
    REQUIRE(audioDevice.playedSamples.empty());
    Adagio::Sample sample = audioLibrary.loadSample("oof.wav");

    SECTION("AudioLibrary can retrieve a sample by name") {
      Adagio::Sample fetchedSample = audioLibrary.getSample("oof.wav"_hs);
      REQUIRE(fetchedSample.handle == sample.handle);
      REQUIRE(fetchedSample.getSecretId() == sample.getSecretId());
    }

    SECTION("AudioService can play it") {
      Adagio::PlayingSound sound = service.play(sample);
      REQUIRE(audioDevice.playedSamples.size() == 1);
      REQUIRE(audioDevice.playedSamples[0] == "oof.wav");

      SECTION("PlayingSound can be adjusted") {
        sound.setVolume(0.5f);
        REQUIRE(audioDevice.playingSoundData[0].volume == 0.5f);

        sound.setPan(1.0f);
        REQUIRE(audioDevice.playingSoundData[0].pan == 1.0f);

        sound.setLooping(true);
        REQUIRE(audioDevice.playingSoundData[0].loop);

        sound.setVolume(1).setPan(0).setLooping(false);
        REQUIRE(audioDevice.playingSoundData[0].volume == 1);
        REQUIRE(audioDevice.playingSoundData[0].pan == 0);
        REQUIRE_FALSE(audioDevice.playingSoundData[0].loop);

        audioDevice.resetPlayingSounds();
      }
    }

    SECTION("AudioLibrary can unload a sample") {
      audioLibrary.unload(sample);
      REQUIRE(sampleLoader.unloaded);
    }
  }

  SECTION("AudioLibrary can load in a stream") {
    REQUIRE(audioDevice.playedStreams.empty());
    Adagio::Stream stream = audioLibrary.loadStream("doopeetime.ogg");

    SECTION("AudioLibrary can fetch a stream by name") {
      Adagio::Stream fetchedStream =
          audioLibrary.getStream("doopeetime.ogg"_hs);
      REQUIRE(fetchedStream.handle == stream.handle);
      REQUIRE(fetchedStream.getSecretId() == stream.getSecretId());
    }

    SECTION("AudioService can play it") {
      Adagio::PlayingSound sound = service.play(stream);
      REQUIRE(audioDevice.playedStreams.size() == 1);
      REQUIRE(audioDevice.playedStreams[0] == "doopeetime.ogg");

      SECTION("PlayingSound can be adjusted") {
        sound.setVolume(0.5f);
        REQUIRE(audioDevice.playingSoundData[0].volume == 0.5f);

        sound.setPan(1.0f);
        REQUIRE(audioDevice.playingSoundData[0].pan == 1.0f);

        sound.setLooping(true);
        REQUIRE(audioDevice.playingSoundData[0].loop);

        sound.setVolume(1).setPan(0).setLooping(false);
        REQUIRE(audioDevice.playingSoundData[0].volume == 1);
        REQUIRE(audioDevice.playingSoundData[0].pan == 0);
        REQUIRE_FALSE(audioDevice.playingSoundData[0].loop);

        audioDevice.resetPlayingSounds();
      }
    }

    SECTION("AudioLibrary can unload a stream") {
      audioLibrary.unload(stream);
      REQUIRE(streamLoader.unloaded);
    }
  }
}
