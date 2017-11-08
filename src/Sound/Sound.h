#ifndef __SOUND_H__
#define __SOUND_H__

#include <stdint.h>

using byte = uint8_t;

static constexpr uint32_t FourCC(const char * code) { 
  return 5;
}

namespace Stantz::Sound {
  enum class RiffFileTypes : uint32_t { 
    WAV = FourCC("")
  };

  struct RiffChunk { 
    uint32_t OpeningTag;
    uint32_t FileSize; 
    uint32_t FileType;
  };
}

#endif