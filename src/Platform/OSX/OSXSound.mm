#include "../Sound.h"

#import <AudioToolbox/AudioQueue.h>

static const SInt32 NumAudioBuffers = 3;
static const SInt32 SampleRate = 44100; // 44.1kHz
static const SInt32 SquareWaveFrequency = 1000; // 1 kHz
static const SInt32 SquareWaveLength = SampleRate / SquareWaveFrequency;
static const SInt32 QueueBufferLength = 10*SquareWaveLength;

static UInt32 SquareWave[SquareWaveLength];

struct AqPlayState {
  AudioStreamBasicDescription dataFormat;
  AudioQueueRef queue;
  AudioQueueBufferRef buffers[NumAudioBuffers];
  bool isRunning;
};

static AqPlayState *globalPlayState;

static void AudioOutputCallback(void *data, AudioQueueRef inAQ, AudioQueueBufferRef inBuffer) {
  auto state = (AqPlayState*) data;
  
  if(!state->isRunning) {
    return;
  }
  
  /* fill the queue buffer */
  auto b = (UInt32 *) inBuffer->mAudioData;
  for(auto i = 0; i < 10; i++) {
    memcpy(b+i*SquareWaveLength, SquareWave, sizeof(UInt32)*SquareWaveLength);
  }
  for(auto i = 0; i < 10*SquareWaveLength; i++) {
    assert(b[i] == 0xFFFFFF7F
           
           
           || b[i] == 0x00000000);
  }
  
  if(true) {
    AudioQueueEnqueueBuffer(state->queue, inBuffer, 0, nullptr);
  } else {
    AudioQueueStop(state->queue, false);
    state->isRunning = false;
  }
}

void Stantz::Platform::Sound::Startup() {
  OSStatus err;
  
  globalPlayState = (AqPlayState*) malloc(sizeof(AqPlayState));
  memset(globalPlayState, 0, sizeof(AqPlayState));
  
  globalPlayState->dataFormat.mBitsPerChannel = 16;
  globalPlayState->dataFormat.mBytesPerFrame = 4;
  globalPlayState->dataFormat.mBytesPerPacket = 4;
  globalPlayState->dataFormat.mChannelsPerFrame = 2;
  globalPlayState->dataFormat.mFormatID = kAudioFormatLinearPCM;
  globalPlayState->dataFormat.mFormatFlags = kAudioFormatFlagIsSignedInteger | kAudioFormatFlagIsPacked;
  globalPlayState->dataFormat.mFramesPerPacket = 1;
  globalPlayState->dataFormat.mReserved = 0;
  globalPlayState->dataFormat.mSampleRate = SampleRate;
  
  /* allocate test wave pattern */
  for(auto i = 0; i < SquareWaveLength; i++) {
    SquareWave[i] = i < SquareWaveLength/2 ? 0xFFFFFF7F : 0x00000000;
  }
  err = AudioQueueNewOutput(&globalPlayState->dataFormat, AudioOutputCallback, globalPlayState, CFRunLoopGetCurrent(), kCFRunLoopCommonModes, 0, &globalPlayState->queue);
  if(err != noErr) {
    return;
  }
  
  globalPlayState->isRunning = true;
  
  /* allocate audio buffers */
  for(auto i = 0; i < NumAudioBuffers; i++) {
    AudioQueueAllocateBuffer(globalPlayState->queue, 4*QueueBufferLength, &globalPlayState->buffers[i]);
    AudioOutputCallback(globalPlayState, globalPlayState->queue, globalPlayState->buffers[i]);
  }

  err = AudioQueueStart(globalPlayState->queue, nullptr);
  if(err != noErr) {
    return;
  }
  do {
    CFRunLoopRunInMode(kCFRunLoopDefaultMode, 0.25, false);
  } while(true);
}

