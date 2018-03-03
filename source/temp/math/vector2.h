#pragma once
#include <cmath>
#include "temp/common/common.h"

namespace temp {
namespace math {

class Vector2 {
 public:
  Vector2(Float32 x = 0.0f, Float32 y = 0.0f) : x_(x), y_(y) {}
  Vector2(const Vector2&) = default;
  Vector2& operator=(const Vector2&) = default;

  ~Vector2() = default;

  Float32& x() { return x_; }
  Float32& y() { return y_; }
  const Float32& x() const { return x_; }
  const Float32& y() const { return y_; }

  inline Vector2& operator+=(const Vector2& rhs) {
    x_ += rhs.x_;
    y_ += rhs.y_;
    return *this;
  }

  inline Vector2& operator-=(const Vector2& rhs) {
    x_ -= rhs.x_;
    y_ -= rhs.y_;
    return *this;
  }

  inline Vector2& operator*=(Float32 scalar) {
    x_ *= scalar;
    y_ *= scalar;
    return *this;
  }

  inline Vector2& operator/=(Float32 scalar) {
    x_ /= scalar;
    y_ /= scalar;
    return *this;
  }

  inline Float32 magnitude() const { return std::sqrt(sqrMagnitude()); }
  inline Float32 sqrMagnitude() const { return x_ * x_ + y_ * y_; }
  inline Vector2 normalized() const { return *this / magnitude(); }

  inline void normalize() { *this = normalized(); }

 private:
  Float32 x_;
  Float32 y_;
};

inline Bool operator==(const Vector2& lhs, const Vector2& rhs) {
  return lhs.x_ == rhs.x_ && lhs.y_ == rhs.y_;
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
  return std::acos(dot(lhs, rhs) / (lhs.magnitude * rhs.magnitude()));
}

inline Float32 distance(const Vector2& lhs, const Vector2& rhs) {
  return (lhs - rhs).magnitude();
}

inline Float32 dot(const Vector2& lhs, const Vector2& rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y();
}

}  // namespace math
}  // namespace temp