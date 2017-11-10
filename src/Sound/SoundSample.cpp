#include "SoundSample.h"

static uint32_t constexpr MakeFourCC(const char * code) {
  return ((uint32_t) code[3]) << 24 | ((uint32_t)code[2]) << 16 | ((uint32_t)code[1]) << 8 | (uint32_t)code[0];
}
static constexpr uint32_t RIFF = MakeFourCC("RIFF");
static constexpr uint32_t WAVE = MakeFourCC("WAVE");
static constexpr uint32_t FMT = MakeFourCC("fmt ");
static constexpr uint32_t DATA = MakeFourCC("data");

struct RiffHeader { 
  uint32_t OpeningTag;
  uint32_t FileSize; 
  uint32_t FileType;       
}; 

struct FormatChunkHeader {
  uint32_t FormatTag; 
  uint32_t FormatChunkSize;
};

struct FormatChunkData {
  Stantz::Common::Sound::WaveFileFormat Tag;
  uint16_t NumChannels; 
  uint32_t SamplesPerSecond; 
  uint32_t BytesPerSecond;
  uint16_t BlockSize; 
  uint16_t BitsPerSample;
};

struct FormatChunkDataExtended {
  uint16_t ExtensionSize;
  uint16_t NumValidBits; 
  uint32_t ChannelMask; 
  uint8_t Subformat[16];
};

struct DataChunk {
  uint32_t Tag; 
  uint32_t Size;
};

std::unique_ptr<Stantz::Common::Sound::SoundSample> Stantz::Common::Sound::SoundSample::LoadFromWaveFile(const std::string &fileName) {
  auto waveFile = Stantz::Platform::File::Create(fileName);

  if(!waveFile->IsOpen()) {
    return nullptr; 
  }

  RiffHeader riffHeader = {};
  FormatChunkHeader formatChunkHeader = {};
  FormatChunkData formatChunkData = {};
  FormatChunkDataExtended formatChunkDataEx = {};
  DataChunk dataChunk = {};

  waveFile->Read(&riffHeader, 0, sizeof(RiffHeader));
  assert(riffHeader.OpeningTag == RIFF && riffHeader.FileType == WAVE);

  waveFile->Read(&formatChunkHeader, 0, sizeof(FormatChunkHeader));
  assert(formatChunkHeader.FormatTag == FMT);

  waveFile->Read(&formatChunkData, 0, sizeof(FormatChunkData));
  assert(formatChunkData.Tag == WaveFileFormat::Pcm);

  if(formatChunkHeader.FormatChunkSize == 40) {
    waveFile->Read(&formatChunkDataEx, 0, sizeof(FormatChunkDataExtended));
  }
  
  waveFile->Read(&dataChunk, 0, sizeof(DataChunk));
  assert(dataChunk.Tag == DATA);

  uint8_t *data = (uint8_t*)malloc(dataChunk.Size);
  waveFile->Read(data, 0, dataChunk.Size);

  return std::unique_ptr<Stantz::Common::Sound::SoundSample>(new SoundSample(
    formatChunkData.Tag, 
    formatChunkData.NumChannels, 
    formatChunkData.SamplesPerSecond, 
    formatChunkData.BytesPerSecond, 
    formatChunkData.BlockSize, 
    0, 
    data, 
    dataChunk.Size
  ));
}