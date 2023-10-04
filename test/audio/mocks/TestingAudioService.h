#ifndef GL_ADAGIO_TESTINGAUDIOSERVICE_H
#define GL_ADAGIO_TESTINGAUDIOSERVICE_H

#include <string>
#include <vector>
#include "../../../src/audio/Audio.h"

class TestingAudioService : public Adagio::AudioService {
public:
    void initialize() override;

    void close() override;

    Adagio::Sample *loadSample(std::string path) override;

    Adagio::Stream *loadStream(std::string path) override;

    void freeSample(Adagio::Sample *sample) override;

    void freeStream(Adagio::Stream *stream) override;

    [[nodiscard]] std::vector<std::string> getOperations() const;

private:
    std::vector<std::string> operations;
};

#endif //GL_ADAGIO_TESTINGAUDIOSERVICE_H
