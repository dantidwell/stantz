#ifndef __ISOUND_H__ 
#define __ISOUND_H__ 

namespace Stantz::Platform { 
  class Sound {
  public:
    static void Startup();
    static void Shutdown();
    static void StartSound();
  };
}

#endif
