#include "Wave.h"

static uint32_t constexpr MakeFourCC(const char * code) {
  return ((uint32_t) code[3]) << 24 | ((uint32_t)code[2]) << 16 | ((uint32_t)code[1]) << 8 | (uint32_t)code[0];
}
static constexpr uint32_t RIFF = MakeFourCC("RIFF");
static constexpr uint32_t WAVE = MakeFourCC("WAVE");
static constexpr uint32_t FMT = MakeFourCC("fmt ");
static constexpr uint32_t DATA = MakeFourCC("data");

enum class WaveFormat : uint16_t {
  PCM = 0x0001, 
  IEEEFloat = 0x0003, 
  ALaw = 0x0006,
  MuLaw = 0x0007,
  Extensible = 0xFFFE
};

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
  WaveFormat Tag; 
  uint16_t NumChannels; 
  uint32_t SamplesPerSecond; 
  uint32_t BytesPerSecond;
  uint16_t BlockSize; 
  uint16_t BitsPerSample;
};

struct DataChunk {
  uint32_t Tag; 
  uint32_t Size;
};

void Stantz::Common::Sound::LoadWaveFile(const std::string &fileName) { 
  auto waveFile = Stantz::Platform::File::Create(fileName);

  if(!waveFile->IsOpen()) {
    return; 
  }

  RiffHeader riffHeader = {};
  FormatChunkHeader formatChunkHeader = {};
  FormatChunkData formatChunkData = {};
  DataChunk dataChunk = {};

  waveFile->Read(&riffHeader, 0, sizeof(RiffHeader));
  assert(riffHeader.OpeningTag == RIFF && riffHeader.FileType == WAVE);

  waveFile->Read(&formatChunkHeader, 0, sizeof(FormatChunkHeader));
  assert(formatChunkHeader.FormatTag == FMT && formatChunkHeader.FormatChunkSize == 16);

  waveFile->Read(&formatChunkData, 0, sizeof(FormatChunkData));
  assert(formatChunkData.Tag == WaveFormat::PCM);

  waveFile->Read(&dataChunk, 0, sizeof(DataChunk));
  assert(dataChunk.Tag == DATA);
}