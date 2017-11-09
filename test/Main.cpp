#define CATCH_CONFIG_MAIN
#include "../ext/include/catch.h"

#include "../src/Platform/Filesystem.h"
#include "../src/Sound/Sound.h"

TEST_CASE("Test") {
  auto wavFile = Stantz::Platform::File::Create("./Data/Sounds/tada.wav");
  
  /* Fail if the file didn't open */ 
  REQUIRE(wavFile->IsOpen());  

  Stantz::Sound::RiffChunk chunk = {};
  wavFile->Read(&chunk, 0, sizeof(chunk));
  
  REQUIRE(false);
}
