#pragma once
#include <cmath>
#include "temp/common/common.h"

namespace temp {
namespace math {

template <typename T>
class Vector2Base {
 public:
  inline Vector2Base() : Vector2Base(static_cast<T>(0), static_cast<T>(0)) {}
  inline explicit Vector2Base(T x, T y) { elements_[0] = x, elements_[1] = y; }
  inline Vector2Base(const Array<T, 2> e) : Vector2Base(e[0], e[1]) {}
  Vector2Base(const Vector2Base&) = default;
  Vector2Base& operator=(const Vector2Base&) = default;
  ~Vector2Base() = default;

  inline T& operator[](Size i) { return elements_[i]; }
  inline const T& operator[](Size i) const { return elements_[i]; }

  inline Vector2Base& operator+=(const Vector2Base& rhs) {
    elements_[0] += rhs.elements_[0];
    elements_[1] += rhs.elements_[1];
    return *this;
  }

  inline Vector2Base& operator-=(const Vector2Base& rhs) {
    elements_[0] -= rhs.elements_[0];
    elements_[1] -= rhs.elements_[1];
    return *this;
  }

  template <typename U>
  inline Vector2Base& operator*=(U scalar) {
    elements_[0] *= scalar;
    elements_[1] *= scalar;
    return *this;
  }

  template <typename U>
  inline Vector2Base& operator/=(U scalar) {
    elements_[0] /= scalar;
    elements_[1] /= scalar;
    return *this;
  }

  inline T& x() { return elements_[0]; }
  inline T& y() { return elements_[1]; }
  inline const T& x() const { return elements_[0]; }
  inline const T& y() const { return elements_[1]; }

  inline T magnitude() const { return std::sqrt(sqrMagnitude()); }
  inline T sqrMagnitude() const { return x() * x() + y() * y(); }
  inline Vector2Base normalized() const { return *this / magnitude(); }

  inline void normalize() { *this = normalized(); }

  static inline Vector2Base zero() { return Vector2Base(); }
  static inline Vector2Base one() {
    return Vector2Base(static_cast<T>(1), static_cast<T>(1));
  }

 private:
  T elements_[2];
};

template <typename T>
inline Bool operator==(const Vector2Base<T>& lhs, const Vector2Base<T>& rhs) {
  return lhs.x() == rhs.x() && lhs.y() == rhs.y();
}

template <typename T>
inline Bool operator!=(const Vector2Base<T>& lhs, const Vector2Base<T>& rhs) {
  return !(lhs == rhs);
}

template <typename T>
inline Vector2Base<T> operator+(const Vector2Base<T>& lhs,
                                const Vector2Base<T>& rhs) {
  auto r = lhs;
  return r += rhs;
}

template <typename T>
inline Vector2Base<T> operator-(const Vector2Base<T>& lhs,
                                const Vector2Base<T>& rhs) {
  auto r = lhs;
  return r -= rhs;
}

template <typename T, typename U>
inline Vector2Base<T> operator*(const Vector2Base<T>& lhs, U rhs) {
  auto r = lhs;
  return r *= rhs;
}

template <typename T, typename U>
inline Vector2Base<T> operator*(U lhs, const Vector2Base<T>& rhs) {
  return rhs * lhs;
}

template <typename T, typename U>
inline Vector2Base<T> operator/(const Vector2Base<T>& lhs, U rhs) {
  auto r = lhs;
  return r /= rhs;
}

template <typename T>
inline T angle(const Vector2Base<T>& lhs, const Vector2Base<T>& rhs) {
  return std::acos(dot(lhs, rhs) / (lhs.magnitude() * rhs.magnitude()));
}

template <typename T>
inline T distance(const Vector2Base<T>& lhs, const Vector2Base<T>& rhs) {
  return (lhs - rhs).magnitude();
}

template <typename T>
inline T dot(const Vector2Base<T>& lhs, const Vector2Base<T>& rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y();
}

template <typename T>
inline Vector2Base<T> lerp(const Vector2Base<T>& a, const Vector2Base<T>& b,
                           T t) {
  return a * (static_cast<T>(1) - t) + b * t;
}

using Vector2 = Vector2Base<Float32>;
using Vector2F64 = Vector2Base<Float64>;

}  // namespace math
}  // namespace temp