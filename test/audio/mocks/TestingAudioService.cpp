#include "TestingAudioService.h"
#include "TestingSample.h"
#include "TestingStream.h"

std::vector<std::string> TestingAudioService::getOperations() const {
    return operations;
}

void TestingAudioService::initialize() {
    operations.emplace_back("initialized");
}

void TestingAudioService::close() {
    operations.emplace_back("closed");
}

Adagio::Sample *TestingAudioService::loadSample(std::string path) {
    return new TestingSample;
}

Adagio::Stream *TestingAudioService::loadStream(std::string path) {
    return new TestingStream;
}

void TestingAudioService::freeSample(Adagio::Sample *sample) {
    delete sample;
}

void TestingAudioService::freeStream(Adagio::Stream *stream) {
    delete stream;
}
