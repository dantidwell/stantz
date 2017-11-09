#include "../Sound.h"

#include <windows.h>
#include <xaudio2.h>

using XAudio2Factory = HRESULT (*)(
  IXAudio2**,
  UINT32,
  XAUDIO2_PROCESSOR
);

static HMODULE XAudio2Library = nullptr; 
static XAudio2Factory _XAudio2Create = nullptr;
static IXAudio2 *xAudio = nullptr; 
static IXAudio2MasteringVoice *xAudioMasteringVoice = nullptr;

void Stantz::Platform::Sound::Startup() {
  XAudio2Library = LoadLibrary(L"XAudio2_9.dll"); 
  if(XAudio2Library == nullptr) { 
    return;
  }
  
  _XAudio2Create = (XAudio2Factory) GetProcAddress(XAudio2Library, "XAudio2Create");
  if(_XAudio2Create == nullptr) { 
    return;
  }

  if(FAILED(_XAudio2Create(&xAudio, 0, XAUDIO2_DEFAULT_PROCESSOR))) { 
    return;
  }

  if(FAILED(xAudio->CreateMasteringVoice(&xAudioMasteringVoice))) { 
    return;
  }
}

void Stantz::Platform::Sound::Shutdown() { 
  if(XAudio2Library != nullptr) { 
    FreeLibrary(XAudio2Library);
  }
}
