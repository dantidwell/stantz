#ifndef __SOUNDSAMPLE_H__ 
#define __SOUNDSAMPLE_H__ 

#include "../Stantz.h"

namespace Stantz::Common::Sound {
  enum class WaveFileFormat : uint16_t {
    Pcm = 0x0001
  };

  class SoundSample { 
  
  public:
    static std::unique_ptr<SoundSample> LoadFromWaveFile(const std::string &fileName);
    
    const WaveFileFormat Format;
    const uint16_t NumChannels; 
    const uint32_t SamplesPerSecond; 
    const uint32_t BytesPerSecond; 
    const uint16_t BlockAlign; 
    const uint16_t ExtensionSize;
    const uint8_t *Buffer;
    const uint32_t BufferSize;
  
    ~SoundSample() {
      if(Buffer != nullptr) { 
        delete Buffer; 
      }  
    }; 

  protected: 
    SoundSample(
      WaveFileFormat format,
      const uint16_t numChannels,
      const uint32_t samplesPerSecond,
      const uint32_t bytesPerSecond,
      const uint16_t blockAlign,
      const uint16_t extensionSize,
      const uint8_t *buffer,
      const uint32_t bufferSize
    ) : 
      Format(format), 
      NumChannels(numChannels), 
      SamplesPerSecond(samplesPerSecond), 
      BytesPerSecond(bytesPerSecond), 
      BlockAlign(blockAlign), 
      ExtensionSize(extensionSize), 
      Buffer(buffer),
      BufferSize(bufferSize)
    {};
  };
};

#endif 