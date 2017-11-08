#include <windows.h>
#include <xaudio2.h>

static IXAudio2 *xAudio = nullptr; 
static IXAudio2MasteringVoice *xAudioMasteringVoice = nullptr;

namespace Stantz::Win32::Sound { 
  void Init(HWND window) {
    if(FAILED(XAudio2Create(&xAudio, 0, XAUDIO2_DEFAULT_PROCESSOR))) { 
      MessageBox(window, L"Sound Not Initialized!", L"Notification", MB_OK);
      return;
    }

    if(FAILED(xAudio->CreateMasteringVoice(&xAudioMasteringVoice))) { 
      MessageBox(window, L"Sound Not Initialized!", L"Notification", MB_OK);      
      return;
    }

    
  }
}