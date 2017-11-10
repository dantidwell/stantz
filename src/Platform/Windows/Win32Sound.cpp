#include "../Sound.h"

#include <windows.h>
#include <xaudio2.h>

using XAudio2Factory = HRESULT (*)(
  IXAudio2**,
  UINT32,
  XAUDIO2_PROCESSOR
);

static XAudio2Factory _XAudio2Create = nullptr;
static IXAudio2 *xAudio = nullptr; 

static IXAudio2MasteringVoice *xAudioMasteringVoice = nullptr;
static IXAudio2SourceVoice *xMusicVoice = nullptr; 

void Stantz::Platform::Sound::Startup() {
  CoInitializeEx(nullptr, 0);

  if(FAILED(XAudio2Create(&xAudio, 0, XAUDIO2_DEFAULT_PROCESSOR))) { 
    return;
  }

  XAUDIO2_DEBUG_CONFIGURATION xAudioDebug = { 0 };
  xAudioDebug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_INFO | XAUDIO2_LOG_WARNINGS | XAUDIO2_LOG_DETAIL;
  //xAudioDebug.BreakMask = XAUDIO2_LOG_ERRORS;
  xAudioDebug.LogFunctionName = true;
  xAudioDebug.LogFileline = true;
  xAudioDebug.LogThreadID = true;
  xAudioDebug.LogTiming = true;

  xAudio->SetDebugConfiguration(&xAudioDebug, nullptr);

  if (FAILED(xAudio->CreateMasteringVoice(&xAudioMasteringVoice))) {
    return;
  }
}

void Stantz::Platform::Sound::Shutdown() { 
}

void Stantz::Platform::Sound::StartSound(const Stantz::Common::Sound::SoundSample &sample) {
 /* initialize the music voice */
 WAVEFORMATEX musicVoiceFormat = { 0 };
 musicVoiceFormat.wFormatTag = (WORD) sample.Format;
 musicVoiceFormat.nChannels = sample.NumChannels;
 musicVoiceFormat.nAvgBytesPerSec = sample.BytesPerSecond;
 musicVoiceFormat.nBlockAlign = sample.BlockAlign;
 musicVoiceFormat.wBitsPerSample = 8; 
 musicVoiceFormat.nSamplesPerSec = sample.SamplesPerSecond;
 musicVoiceFormat.cbSize = sample.ExtensionSize;

 XAUDIO2_BUFFER buffer = { 0 };
 buffer.AudioBytes = sample.BufferSize;
 buffer.Flags = XAUDIO2_END_OF_STREAM;
 buffer.LoopBegin = 0;
 buffer.LoopCount = 0;
 buffer.LoopLength = 0;
 buffer.pAudioData = sample.Buffer;
 buffer.PlayLength = sample.BufferSize;
 buffer.PlayBegin = 0; 

 if (FAILED(xAudio->CreateSourceVoice(&xMusicVoice, (WAVEFORMATEX*) &musicVoiceFormat))) {
   return;
 }

 if (FAILED(xMusicVoice->SubmitSourceBuffer(&buffer))) {
   /* TODO: log failure */
   return;
 }
 if (FAILED(xMusicVoice->Start())) {
   /* TODO: log failure */
   return;
 }
}