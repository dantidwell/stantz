#ifndef __FILESYSTEM_H__ 
#define __FILESYSTEM_H__ 

#include <stdint.h>
#include <memory>
#include <string>

namespace Stantz::Platform {
  enum class FileOpenMode { 
    READ_ONLY
  };
  
  class File {
  public:
    static std::unique_ptr<File> Create(const std::string &fileName);
    virtual ~File() {};

    const std::string Name;

    virtual bool IsOpen() = 0;
    virtual int Read(void *buffer, int32_t offset, int32_t count) = 0;
  protected:
    File(const std::string &name) : 
      Name(name) 
    {}
  };
  
  class FileSystem {
  public:
    static const std::string GetCurrentWorkingDirectory();
  };
};

#endif
