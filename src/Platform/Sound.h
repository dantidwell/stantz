#ifndef __ISOUND_H__ 
#define __ISOUND_H__ 

#include "../Sound/Sound.h"

namespace Stantz::Platform { 
  class Sound {
  public:
    static void Startup();
    static void Shutdown();
    static void StartSound(const Stantz::Common::Sound::SoundSample &sample);
  };
}

#endif
