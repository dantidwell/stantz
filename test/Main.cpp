#define CATCH_CONFIG_MAIN
#include "../ext/include/catch.h"

#include "../src/Sound/Sound.h"

TEST_CASE("WaveFile") {
  Stantz::Common::Sound::LoadWaveFile(
    "./Data/Sounds/tada.wav"
  );
  REQUIRE(false);
}
