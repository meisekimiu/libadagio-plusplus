#ifndef GL_ADAGIO_AUDIODEVICE_H
#define GL_ADAGIO_AUDIODEVICE_H

#include "AudioLibrary.h"
#include "Sample.h"
#include "Stream.h"

namespace Adagio {
template <class SampleType, class StreamType> class AudioDevice {
public:
  virtual void
  playSample(const Sample &sample,
             AudioLibrary<SampleType, StreamType> &audioLibrary) = 0;

  virtual void
  playStream(const Stream &stream,
             AudioLibrary<SampleType, StreamType> &audioLibrary) = 0;
};
} // namespace Adagio

#endif // GL_ADAGIO_AUDIODEVICE_H
