#pragma once
#include "temp/common/common.h"
#include "temp/math/vector3.h"

namespace temp {
namespace math {

class Vector4;
Bool operator==(const Vector4& lhs, const Vector4& rhs);
Bool operator!=(const Vector4& lhs, const Vector4& rhs);
Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
Vector4 operator*(const Vector4& lhs, Float32 rhs);
Vector4 operator*(Float32 lhs, const Vector4& rhs);
Vector4 operator/(const Vector4& lhs, Float32 rhs);
Float32 dot(const Vector4& lhs, const Vector4& rhs);

class Vector4 {
 public:
  Vector4() : Vector4(0.0f, 0.0f, 0.0f, 0.0f) {}
  explicit Vector4(Float32 x, Float32 y, Float32 z, Float32 w) {
	  elements_[0] = x, elements_[1] = y, elements_[2] = z, elements_[3] = w;
  }
  explicit Vector4(const Array<Float32, 4> e)
      : Vector4(e[0], e[1], e[2], e[3]) {}
  explicit Vector4(const Vector3& vec3, Float32 w = 1.0f)
      : Vector4(vec3.x(), vec3.y(), vec3.z(), w) {}
  Vector4(const Vector4&) = default;
  Vector4& operator=(const Vector4&) = default;
  ~Vector4() = default;

  operator Vector3() const { return Vector3(x(), y(), z()); }
  Float32& operator[](Size i) { return elements_[i]; }
  const Float32& operator[](Size i) const { return elements_[i]; }

  inline Vector4& operator+=(const Vector4& rhs) {
    for (int i = 0; i < 4; ++i) {
      elements_[i] += rhs.elements_[i];
    }
    return *this;
  }

  inline Vector4& operator-=(const Vector4& rhs) {
    for (int i = 0; i < 4; ++i) {
      elements_[i] -= rhs.elements_[i];
    }
    return *this;
  }

  inline Vector4& operator*=(Float32 scalar) {
    for (int i = 0; i < 4; ++i) {
      elements_[i] *= scalar;
    }
    return *this;
  }

  inline Vector4& operator/=(Float32 scalar) {
    for (int i = 0; i < 4; ++i) {
      elements_[i] /= scalar;
    }
    return *this;
  }

  inline Float32 magnitude() const { return std::sqrt(sqrMagnitude()); }
  inline Float32 sqrMagnitude() const {
    return x() * x() + y() * y() + z() * z() + w() * w();
  }
  inline Vector4 normalized() const { return *this / magnitude(); }

  inline void normalize() { *this = normalized(); }

  Float32& x() { return elements_[0]; }
  Float32& y() { return elements_[1]; }
  Float32& z() { return elements_[2]; }
  Float32& w() { return elements_[3]; }
  const Float32& x() const { return elements_[0]; }
  const Float32& y() const { return elements_[1]; }
  const Float32& z() const { return elements_[2]; }
  const Float32& w() const { return elements_[3]; }

  static inline Vector4 zero() { return Vector4(); }
  static inline Vector4 one() { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }

 private:
  Float32 elements_[4];
};

inline Bool operator==(const Vector4& lhs, const Vector4& rhs) {
  return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z() &&
         lhs.w() == rhs.w();
}

inline Bool operator!=(const Vector4& lhs, const Vector4& rhs) {
  return !(lhs == rhs);
}

inline Vector4 operator+(const Vector4& lhs, const Vector4& rhs) {
  auto r = lhs;
  return r += rhs;
}

inline Vector4 operator-(const Vector4& lhs, const Vector4& rhs) {
  auto r = lhs;
  return r -= rhs;
}

inline Vector4 operator*(const Vector4& lhs, Float32 rhs) {
  auto r = lhs;
  return r *= rhs;
}

inline Vector4 operator*(Float32 lhs, const Vector4& rhs) { return rhs * lhs; }

inline Vector4 operator/(const Vector4& lhs, Float32 rhs) {
  auto r = lhs;
  return r /= rhs;
}

inline Float32 dot(const Vector4& lhs, const Vector4& rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z() +
         lhs.w() * rhs.w();
}

}  // namespace math
}  // namespace temp
