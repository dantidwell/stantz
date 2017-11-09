#ifndef __OSX_FILESYSTEM_H__ 
#define __OSX_FILESYSTEM_H__

#include "../Filesystem.h"
#import <Foundation/Foundation.h>

namespace Stantz::Platform { 
  class OSXFile : public Stantz::Platform::File { 
  public:
    OSXFile(const std::string &fileName);
    ~OSXFile();
    bool IsOpen();
    int Read(void *buffer, int32_t offset, int32_t count);
  private: 
    NSFileHandle *osxFileHandle;
  };
}

#endif
