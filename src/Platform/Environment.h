#ifndef __ENVIONMENT_H__
#define __ENVIONMENT_H__

#include <string>

namespace Stantz::Platform { 
  class Environment { 
  public: 
    static const std::string GetVariable(const std::string &name);
  };
}

#endif