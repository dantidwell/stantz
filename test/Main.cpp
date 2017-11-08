#define CATCH_CONFIG_MAIN
#include "../ext/include/catch.h"

#include <windows.h>
#define DIR_BUFFER_LENGTH 256

// #include "../src/Sound/sound.h"
#include "../src/Platform/Filesystem.h"

TEST_CASE("Test") {
  auto wavFile = Stantz::Platform::File::Create("Data\\Sounds\\tada.wav");
  
  /* Fail if the file didn't open */ 
  REQUIRE(wavFile->IsOpen());  
}
