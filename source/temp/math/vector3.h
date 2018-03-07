#pragma once
#include "temp/common/common.h"
#include "temp/math/vector2.h"

namespace temp {
namespace math {

class Vector3;
Bool operator==(const Vector3& lhs, const Vector3& rhs);
Bool operator!=(const Vector3& lhs, const Vector3& rhs);
Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
Vector3 operator*(const Vector3& lhs, Float32 rhs);
Vector3 operator*(Float32 lhs, const Vector3& rhs);
Vector3 operator/(const Vector3& lhs, Float32 rhs);
Float32 angle(const Vector3& lhs, const Vector3& rhs);
Float32 distance(const Vector3& lhs, const Vector3& rhs);
Float32 dot(const Vector3& lhs, const Vector3& rhs);
Vector3 cross(const Vector3& lhs, const Vector3& rhs);
Vector3 lerp(const Vector3& a, const Vector3& b, Float32 t);

class Vector3 {
 public:
  Vector3() : Vector3(0.0f, 0.0f, 0.0f) {}
  explicit Vector3(Float32 x, Float32 y, Float32 z) {
    elements_[0] = x, elements_[1] = y, elements_[2] = z;
  }
  explicit Vector3(const Array<Float32, 3> e) : Vector3(e[0], e[1], e[2]) {}
  explicit Vector3(const Vector2& vec2, Float32 z)
      : Vector3(vec2.x(), vec2.y(), z) {}
  Vector3(const Vector3&) = default;
  Vector3& operator=(const Vector3&) = default;
  ~Vector3() = default;

  Float32& operator[](Size i) { return elements_[i]; }
  const Float32& operator[](Size i) const { return elements_[i]; }

  inline Vector3& operator+=(const Vector3& rhs) {
    for (int i = 0; i < 3; ++i) {
      elements_[i] += rhs.elements_[i];
    }
    return *this;
  }

  inline Vector3& operator-=(const Vector3& rhs) {
    for (int i = 0; i < 3; ++i) {
      elements_[i] -= rhs.elements_[i];
    }
    return *this;
  }

  inline Vector3& operator*=(Float32 scalar) {
    for (int i = 0; i < 3; ++i) {
      elements_[i] *= scalar;
    }
    return *this;
  }

  inline Vector3& operator/=(Float32 scalar) {
    for (int i = 0; i < 3; ++i) {
      elements_[i] /= scalar;
    }
    return *this;
  }

  inline Float32 magnitude() const { return std::sqrt(sqrMagnitude()); }
  inline Float32 sqrMagnitude() const {
    return x() * x() + y() * y() + z() * z();
  }
  inline Vector3 normalized() const { return *this / magnitude(); }

  inline void normalize() { *this = normalized(); }

  Float32& x() { return elements_[0]; }
  Float32& y() { return elements_[1]; }
  Float32& z() { return elements_[2]; }
  const Float32& x() const { return elements_[0]; }
  const Float32& y() const { return elements_[1]; }
  const Float32& z() const { return elements_[2]; }

  static inline Vector3 zero() { return Vector3(0.0f, 0.0f, 0.0f); }
  static inline Vector3 one() { return Vector3(1.0f, 1.0f, 1.0f); }
  static inline Vector3 forward() { return Vector3(0.0f, 0.0f, 1.0f); }
  static inline Vector3 backward() { return Vector3(0.0f, 0.0f, -1.0f); }
  static inline Vector3 right() { return Vector3(1.0f, 0.0f, 0.0f); }
  static inline Vector3 left() { return Vector3(-1.0f, 0.0f, 0.0f); }
  static inline Vector3 up() { return Vector3(0.0f, 1.0f, 0.0f); }
  static inline Vector3 down() { return Vector3(0.0f, -1.0f, 0.0f); }

 private:
  Float32 elements_[3];
};

inline Bool operator==(const Vector3& lhs, const Vector3& rhs) {
  return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z();
}

inline Bool operator!=(const Vector3& lhs, const Vector3& rhs) {
  return !(lhs == rhs);
}

inline Vector3 operator+(const Vector3& lhs, const Vector3& rhs) {
  auto r = lhs;
  return r += rhs;
}

inline Vector3 operator-(const Vector3& lhs, const Vector3& rhs) {
  auto r = lhs;
  return r -= rhs;
}

inline Vector3 operator*(const Vector3& lhs, Float32 rhs) {
  auto r = lhs;
  return r *= rhs;
}

inline Vector3 operator*(Float32 lhs, const Vector3& rhs) { return rhs * lhs; }

inline Vector3 operator/(const Vector3& lhs, Float32 rhs) {
  auto r = lhs;
  return r /= rhs;
}

inline Float32 angle(const Vector3& lhs, const Vector3& rhs) {
  return acos(dot(lhs, rhs) / (lhs.magnitude() * rhs.magnitude()));
}

inline Float32 distance(const Vector3& lhs, const Vector3& rhs) {
  return (lhs - rhs).magnitude();
}

inline Float32 dot(const Vector3& lhs, const Vector3& rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

inline Vector3 cross(const Vector3& lhs, const Vector3& rhs) {
  return Vector3(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
                 lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                 lhs.x() * rhs.y() - lhs.y() * rhs.x());
}

inline Vector3 lerp(const Vector3& a, const Vector3& b, Float32 t) {
  return a * (1.0f - t) + b * t;
}

}  // namespace math
}  // namespace temp
