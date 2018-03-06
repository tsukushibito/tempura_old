#pragma once
#include <cmath>
#include "temp/common/common.h"

namespace temp {
namespace math {

class Vector2;
Bool operator==(const Vector2& lhs, const Vector2& rhs);
Bool operator!=(const Vector2& lhs, const Vector2& rhs);
Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
Vector2 operator*(const Vector2& lhs, Float32 rhs);
Vector2 operator*(Float32 lhs, const Vector2& rhs);
Vector2 operator/(const Vector2& lhs, Float32 rhs);
Float32 angle(const Vector2& lhs, const Vector2& rhs);
Float32 distance(const Vector2& lhs, const Vector2& rhs);
Float32 dot(const Vector2& lhs, const Vector2& rhs);
Vector2 lerp(const Vector2& a, const Vector2& b, Float32 t);

class Vector2 {
 public:
  Vector2() : Vector2(0.0f, 0.0f) {}
  explicit Vector2(Float32 x, Float32 y) { elements_[0] = x, elements_[1] = y; }
  Vector2(const Array<Float32, 2> e) : Vector2(e[0], e[1]) {}
  Vector2(const Vector2&) = default;
  Vector2& operator=(const Vector2&) = default;
  ~Vector2() = default;

  Float32& operator[](Size i) { return elements_[i]; }
  const Float32& operator[](Size i) const { return elements_[i]; }

  inline Vector2& operator+=(const Vector2& rhs) {
    elements_[0] += rhs.elements_[0];
    elements_[1] += rhs.elements_[1];
    return *this;
  }

  inline Vector2& operator-=(const Vector2& rhs) {
    elements_[0] -= rhs.elements_[0];
    elements_[1] -= rhs.elements_[1];
    return *this;
  }

  inline Vector2& operator*=(Float32 scalar) {
    elements_[0] *= scalar;
    elements_[1] *= scalar;
    return *this;
  }

  inline Vector2& operator/=(Float32 scalar) {
    elements_[0] /= scalar;
    elements_[1] /= scalar;
    return *this;
  }

  Float32& x() { return elements_[0]; }
  Float32& y() { return elements_[1]; }
  const Float32& x() const { return elements_[0]; }
  const Float32& y() const { return elements_[1]; }

  inline Float32 magnitude() const { return std::sqrt(sqrMagnitude()); }
  inline Float32 sqrMagnitude() const { return x() * x() + y() * y(); }
  inline Vector2 normalized() const { return *this / magnitude(); }

  inline void normalize() { *this = normalized(); }

  static inline Vector2 zero() { return Vector2(0.0f, 0.0f); }
  static inline Vector2 one() { return Vector2(1.0f, 1.0f); }

 private:
  Float32 elements_[2];
};

inline Bool operator==(const Vector2& lhs, const Vector2& rhs) {
  return lhs.x() == rhs.x() && lhs.y() == rhs.y();
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

inline Vector2 operator*(const Vector2& lhs, Float32 rhs) {
  auto r = lhs;
  return r *= rhs;
}

inline Vector2 operator*(Float32 lhs, const Vector2& rhs) { return rhs * lhs; }

inline Vector2 operator/(const Vector2& lhs, Float32 rhs) {
  auto r = lhs;
  return r /= rhs;
}

inline Float32 angle(const Vector2& lhs, const Vector2& rhs) {
  return std::acos(dot(lhs, rhs) / (lhs.magnitude() * rhs.magnitude()));
}

inline Float32 distance(const Vector2& lhs, const Vector2& rhs) {
  return (lhs - rhs).magnitude();
}

inline Float32 dot(const Vector2& lhs, const Vector2& rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y();
}

inline Vector2 lerp(const Vector2& a, const Vector2& b, Float32 t) {
  return a * (1.0f - t) + b * t;
}

}  // namespace math
}  // namespace temp