#ifndef __PLANE_H__
#define __PLANE_H__

#include "Vector.h"

namespace Stantz::Geometry { 
  struct Plane {
    const Vector3 Normal; 
    const float NormalOffset;
  };
}

#endif