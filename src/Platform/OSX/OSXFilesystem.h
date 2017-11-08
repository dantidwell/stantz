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
  private: 
    NSFileHandle *osxFileHandle;
  };
}

#endif