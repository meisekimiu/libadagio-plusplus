#ifndef GL_ADAGIO_SOLOUDAUDIODEVICE_H
#define GL_ADAGIO_SOLOUDAUDIODEVICE_H

#include "../../audio/AudioDevice.h"
#include "SoloudSampleLoader.h"
#include "SoLoudStreamLoader.h"
#include <soloud.h>
#include <soloud_wav.h>
#include <soloud_wavstream.h>

class SoloudAudioDevice : public Adagio::AudioDevice<SoLoud::Wav, SoLoud::WavStream> {
public:
    explicit SoloudAudioDevice(SoLoud::Soloud &soloud);
    
    Adagio::PlayingSoundHandle
    playSample(const Adagio::Sample &sample) override;

    Adagio::PlayingSoundHandle
    playStream(const Adagio::Stream &stream) override;

    void setLooping(Adagio::PlayingSoundHandle handle, bool loop) override;

    void setPlayingPan(Adagio::PlayingSoundHandle handle, float pan) override;

    void setPlayingVolume(Adagio::PlayingSoundHandle handle, float volume) override;

private:
    SoLoud::Soloud &soloud;
    SoloudSampleLoader sampleLoader;
    SoloudStreamLoader streamLoader;
};


#endif //GL_ADAGIO_SOLOUDAUDIODEVICE_H
