#ifndef __VECTOR_H__
#define __VECTOR_H__

namespace Stantz::Geometry { 
  struct Vector3 { 
    const float X;
    const float Y; 
    const float Z;

    float Norm() const;
    float InnerProduct(const Vector3 &other) const;
    const Vector3 CrossProduct(const Vector3 &other) const;
  };
}

#endif