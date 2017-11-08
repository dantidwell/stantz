#include "Vector.h"

#include <cmath>

float Stantz::Vector3::Norm() const { 
  return std::sqrt(InnerProduct(*this));
}

float Stantz::Vector3::InnerProduct(const Vector3 &other) const { 
  return X*other.X 
  + Y*other.Y 
  + Z*other.Z;
}

const Stantz::Vector3 Stantz::Vector3::CrossProduct(const Vector3 &other) const { 
  return Vector3 { 
    Y*other.Z, 
    Z*other.X, 
    X*other.Y
  };
}
