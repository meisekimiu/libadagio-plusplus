#ifndef GL_ADAGIO_ECSMOCKAUDIODEVICE_H
#define GL_ADAGIO_ECSMOCKAUDIODEVICE_H

#include "../../../src/audio/AudioDevice.h"
#include "EcsMockAudioLibrary.h"
#include "NullSound.h"

class EcsMockAudioDevice : public Adagio::AudioDevice<NullSound, NullSound> {
public:
  EcsMockAudioDevice();

  Adagio::PlayingSoundHandle playSample(const Adagio::Sample &sample) override;

  Adagio::PlayingSoundHandle playStream(const Adagio::Stream &stream) override;

  void setPlayingVolume(Adagio::PlayingSoundHandle handle,
                        float volume) override;

  void setPlayingPan(Adagio::PlayingSoundHandle handle, float pan) override;

  void setLooping(Adagio::PlayingSoundHandle handle, bool loop) override;

  Adagio::AbstractAudioLibrary &getAudioLibrary() override;

  void stopAll() override;

  void stop(Adagio::PlayingSoundHandle handle) override;

private:
  EcsMockAudioLibrary mockLibrary;
  EcsNullSoundLoader loader;
};

#endif // GL_ADAGIO_ECSMOCKAUDIODEVICE_H
