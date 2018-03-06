#pragma once
#include "temp/math/matrix4x4.h"
namespace temp {
namespace math {
inline Float32 Matrix4x4::determinant() const {
  auto&& self = *this;
  Float32 d;
  d = self(0, 0) * self(1, 1) * self(2, 2) * self(3, 3) +  //
      self(0, 0) * self(1, 2) * self(2, 3) * self(3, 1) +  //
      self(0, 0) * self(1, 3) * self(2, 1) * self(3, 2) -  //

      self(0, 0) * self(1, 3) * self(2, 2) * self(3, 1) -  //
      self(0, 0) * self(1, 2) * self(2, 1) * self(3, 3) -  //
      self(0, 0) * self(1, 1) * self(2, 3) * self(3, 2) -  //

      self(0, 1) * self(1, 0) * self(2, 2) * self(3, 3) -  //
      self(0, 2) * self(1, 0) * self(2, 3) * self(3, 1) -  //
      self(0, 3) * self(1, 0) * self(2, 1) * self(3, 2) +  //

      self(0, 3) * self(1, 0) * self(2, 2) * self(3, 1) +  //
      self(0, 2) * self(1, 0) * self(2, 1) * self(3, 3) +  //
      self(0, 1) * self(1, 0) * self(2, 3) * self(3, 2) +  //

      self(0, 1) * self(1, 2) * self(2, 0) * self(3, 3) +  //
      self(0, 2) * self(1, 3) * self(2, 0) * self(3, 1) +  //
      self(0, 3) * self(1, 1) * self(2, 0) * self(3, 2) -  //

      self(0, 3) * self(1, 2) * self(2, 0) * self(3, 1) -  //
      self(0, 2) * self(1, 1) * self(2, 0) * self(3, 3) -  //
      self(0, 1) * self(1, 3) * self(2, 0) * self(3, 2) -  //

      self(0, 1) * self(1, 2) * self(2, 3) * self(3, 0) -  //
      self(0, 2) * self(1, 3) * self(2, 1) * self(3, 0) -  //
      self(0, 3) * self(1, 1) * self(2, 2) * self(3, 0) +  //

      self(0, 3) * self(1, 2) * self(2, 1) * self(3, 0) +  //
      self(0, 2) * self(1, 1) * self(2, 3) * self(3, 0) +  //
      self(0, 1) * self(1, 3) * self(2, 2) * self(3, 0);   //
  return d;
}

inline Matrix4x4 Matrix4x4::inversed() const { return Matrix4x4(); }
}  // namespace math
}  // namespace temp