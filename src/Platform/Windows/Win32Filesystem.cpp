#include "Win32Filesystem.h"

#define WINDOWS_DIR_BUFFER_LENGTH 256

/**
 * Win32 File Implementation 
 */

std::unique_ptr<Stantz::Platform::File> Stantz::Platform::File::Create(const std::string &fileName) { 
  return std::make_unique<Stantz::Platform::Win32File>(fileName);
} 

Stantz::Platform::Win32File::Win32File(const std::string &name) : 
  Stantz::Platform::File::File(name)
{
  auto numWCharsToAllocate = MultiByteToWideChar(
    CP_UTF8, 
    MB_ERR_INVALID_CHARS, 
    Name.c_str(), 
    -1,
    NULL, 
    0 
  );

  auto win32WideFileName = std::make_unique<wchar_t[]>(numWCharsToAllocate);
  
  MultiByteToWideChar(
    CP_UTF8, 
    MB_ERR_INVALID_CHARS, 
    Name.c_str(), 
    -1,
    win32WideFileName.get(), 
    numWCharsToAllocate 
  );
  
  win32FileHandle = CreateFileW(
    win32WideFileName.get(), 
    GENERIC_READ, 
    0, 
    NULL, 
    OPEN_EXISTING,
    FILE_ATTRIBUTE_NORMAL, 
    NULL
  );
}

Stantz::Platform::Win32File::~Win32File() { 
  CloseHandle(win32FileHandle);
}


bool Stantz::Platform::Win32File::IsOpen() { 
  return win32FileHandle != INVALID_HANDLE_VALUE;  
}

int Stantz::Platform::Win32File::Read(void *buffer, int32_t offset, int32_t count) { 
  UNREFERENCED_PARAMETER(offset);
  
  DWORD numBytesRead = 0;
  
  auto result = ReadFile(
    win32FileHandle,
    buffer,
    count,
    &numBytesRead,
    nullptr
  );

  if(!result) { 
    return 0;
  }
  return numBytesRead;
}