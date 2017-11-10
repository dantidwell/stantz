#define CATCH_CONFIG_MAIN
#include "../ext/include/catch.h"

#include "../src/Platform/Sound.h"
#include "../src/Sound/Sound.h"

TEST_CASE("WaveFile") {
  Stantz::Platform::Sound::Startup();

  auto sample = Stantz::Common::Sound::SoundSample::LoadFromWaveFile(
    "./Data/Sounds/tada.wav"
  );
  
  Stantz::Platform::Sound::StartSound(*sample);

  Sleep(2000);
}
