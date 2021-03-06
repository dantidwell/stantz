#include "./OSXFilesystem.h"

std::unique_ptr<Stantz::Platform::File> Stantz::Platform::File::Create(const std::string &fileName) { 
  return std::make_unique<Stantz::Platform::OSXFile>(fileName);
}

Stantz::Platform::OSXFile::OSXFile(const std::string &fileName) 
  : File(fileName)
{ 
  NSString *platformFileName = [NSString stringWithCString:Name.c_str() encoding:[NSString defaultCStringEncoding]]; 
  osxFileHandle = [NSFileHandle fileHandleForReadingAtPath: platformFileName];
  [platformFileName release];
}

Stantz::Platform::OSXFile::~OSXFile() { 
  [osxFileHandle closeFile];
}

bool Stantz::Platform::OSXFile::IsOpen() { 
  return osxFileHandle != nil; 
}

int Stantz::Platform::OSXFile::Read(void *buffer, int32_t offset, int32_t count) {
  NSData *result = [osxFileHandle readDataOfLength:count];
  auto numBytesRead = result.length;
  
  memcpy(buffer, result.bytes, numBytesRead);
  
  [result release];
  return numBytesRead;
};
