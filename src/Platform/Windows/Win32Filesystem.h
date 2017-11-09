#ifndef __WIN32_FILESYSTEM_H__ 
#define __WIN32_FILESYSTEM_H__

#include <windows.h>

#include "../Filesystem.h"

namespace Stantz::Platform { 
  class Win32File : public Stantz::Platform::File { 
  public:
    Win32File(const std::string &fileName);
    ~Win32File();
    bool IsOpen();
    int Read(void *buffer, int32_t offset, int32_t count);
  private: 
    HANDLE win32FileHandle;
  };
}

#endif