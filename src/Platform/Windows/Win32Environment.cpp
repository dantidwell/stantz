#include "../Environment.h"

#include <memory>
#include <windows.h>

const std::string Stantz::Platform::Environment::GetVariable(const std::string &name) { 
  auto bufferSize = GetEnvironmentVariableA(
    name.c_str(), 
    NULL, 
    0
  );

  auto buffer = std::make_unique<char[]>(bufferSize);
  
  GetEnvironmentVariableA(
    name.c_str(), 
    buffer.get(), 
    bufferSize
  );

  return std::string(buffer.get());
}