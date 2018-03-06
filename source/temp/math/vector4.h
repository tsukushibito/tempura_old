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
  explicit Vector4(Float32 x, Float32 y, Float32 z, Float32 w)
      : x_(x), y_(y), z_(z), _w(w) {}
  explicit Vector4(const Vector3& vec3, Float32 w = 1.0f)
      : x_(vec3.x()), y_(vec3.y()), z_(vec3.z()), w_(w) {}
  Vector4(const Vector4&) = default;
  Vector4& operator=(const Vector4&) = default;
  ~Vector4() = default;

  Float32& x() { return x_; }
  Float32& y() { return y_; }
  Float32& z() { return z_; }
  Float32& w() { return w_; }
  const Float32& x() const { return x_; }
  const Float32& y() const { return y_; }
  const Float32& z() const { return z_; }
  const Float32& w() const { return w_; }

  inline Vector4& operator+=(const Vector4& rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    z_ += rhs.z_;
    w_ += rhs.w_;
    return *this;
  }

  inline Vector4& operator-=(const Vector4& rhs) {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    z_ -= rhs.z_;
    w_ -= rhs.w_;
    return *this;
  }

  inline Vector4& operator*=(Float32 scalar) {
    x_ *= scalar;
    y_ *= scalar;
    z_ *= scalar;
    w_ *= scalar;
    return *this;
  }

  inline Vector4& operator/=(Float32 scalar) {
    x_ /= scalar;
    y_ /= scalar;
    z_ /= scalar;
    w_ /= scalar;
    return *this;
  }

  inline Float32 magnitude() const { return std::sqrt(sqrMagnitude()); }
  inline Float32 sqrMagnitude() const {
    return x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_;
  }
  inline Vector4 normalized() const { return *this / magnitude(); }

  inline void normalize() { *this = normalized(); }

  static inline Vector4 zero() { return Vector4(); }
  static inline Vector4 one() { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }

 private:
  Float32 x_;
  Float32 y_;
  Float32 z_;
  Float32 w_;
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

inline Vector4 dot(const Vector4& lhs, const Vector4& rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z() +
         lhs.w() * rhs.w();
}

}  // namespace math
}  // namespace temp
