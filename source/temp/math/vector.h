#pragma once
#include "temp/common/common.h"

namespace temp {
namespace math {
struct Vector2 {
  Float32 x;
  Float32 y;

  inline Vector2& operator+=(const Vector2& rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }

  inline Vector2& operator-=(const Vector2& rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }
};

inline Bool operator==(const Vector2& lhs, const Vector2& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline Bool operator!=(const Vector2& lhs, const Vector2& rhs) {
  return !(lhs == rhs);
}

inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) {
  auto r = lhs;
  return r += rhs;
}

inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs) {
  auto r = lhs;
  return r -= rhs;
}

}  // namespace math
}  // namespace temp