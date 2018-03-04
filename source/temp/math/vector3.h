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
  explicit Vector3(Float32 x = 0.0f, Float32 y = 0.0f, Float32 z = 0.0f)
      : x_(x), y_(y), z_(z) {}
  explicit Vector3(const Vector2& vec2, Float32 z)
      : x_(vec2.x()), y_(vec2.y()), z_(z) {}
  Vector3(const Vector3&) = default;
  Vector3& operator=(const Vector3&) = default;
  ~Vector3() = default;

  Float32& x() { return x_; }
  Float32& y() { return y_; }
  Float32& z() { return z_; }
  const Float32& x() const { return x_; }
  const Float32& y() const { return y_; }
  const Float32& z() const { return z_; }

  inline Vector3& operator+=(const Vector3& rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
    return *this;
  }

  inline Vector3& operator-=(const Vector3& rhs) {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
    return *this;
  }

  inline Vector3& operator*=(Float32 scalar) {
    x_ *= scalar;
    y_ *= scalar;
    z_ *= scalar;
    return *this;
  }

  inline Vector3& operator/=(Float32 scalar) {
    x_ /= scalar;
    y_ /= scalar;
    z_ /= scalar;
    return *this;
  }

  inline Float32 magnitude() const { return std::sqrt(sqrMagnitude()); }
  inline Float32 sqrMagnitude() const { return x_ * x_ + y_ * y_ + z_ * z_; }
  inline Vector3 normalized() const { return *this / magnitude(); }

  inline void normalize() { *this = normalized(); }

 private:
  Float32 x_;
  Float32 y_;
  Float32 z_;
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

inline Vector3 vec3Zero() { return Vector3(0.0f, 0.0f, 0.0f); }
inline Vector3 vec3One() { return Vector3(1.0f, 1.0f, 1.0f); }
inline Vector3 vec3Forward() { return Vector3(0.0f, 0.0f, 1.0f); }
inline Vector3 vec3Backward() { return Vector3(0.0f, 0.0f, -1.0f); }
inline Vector3 vec3Right() { return Vector3(1.0f, 0.0f, 0.0f); }
inline Vector3 vec3Left() { return Vector3(-1.0f, 0.0f, 0.0f); }
inline Vector3 vec3Up() { return Vector3(0.0f, 1.0f, 0.0f); }
inline Vector3 vec3Down() { return Vector3(0.0f, -1.0f, 0.0f); }
}  // namespace math
}  // namespace temp
