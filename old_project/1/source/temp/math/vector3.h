#pragma once
#include "temp/common/common.h"
#include "temp/math/vector2.h"

namespace temp {
namespace math {

template <typename T>
class Vector3Base {
 public:
  Vector3Base()
      : Vector3Base(static_cast<T>(0), static_cast<T>(0.), static_cast<T>(0)) {}
  explicit Vector3Base(T x, T y, T z) {
    elements_[0] = x, elements_[1] = y, elements_[2] = z;
  }
  explicit Vector3Base(const Array<T, 3> e) : Vector3Base(e[0], e[1], e[2]) {}
  explicit Vector3Base(const Vector2Base<T>& vec2, T z)
      : Vector3Base(vec2.x(), vec2.y(), z) {}
  Vector3Base(const Vector3Base&) = default;
  Vector3Base& operator=(const Vector3Base&) = default;
  ~Vector3Base() = default;

  inline T& operator[](Size i) { return elements_[i]; }
  inline const T& operator[](Size i) const { return elements_[i]; }

  inline Vector3Base& operator+=(const Vector3Base& rhs) {
    for (int i = 0; i < 3; ++i) {
      elements_[i] += rhs.elements_[i];
    }
    return *this;
  }

  inline Vector3Base& operator-=(const Vector3Base& rhs) {
    for (int i = 0; i < 3; ++i) {
      elements_[i] -= rhs.elements_[i];
    }
    return *this;
  }

  template <typename U>
  inline Vector3Base& operator*=(U scalar) {
    for (int i = 0; i < 3; ++i) {
      elements_[i] *= scalar;
    }
    return *this;
  }

  template <typename U>
  inline Vector3Base& operator/=(U scalar) {
    for (int i = 0; i < 3; ++i) {
      elements_[i] /= scalar;
    }
    return *this;
  }

  inline T magnitude() const { return std::sqrt(sqrMagnitude()); }
  inline T sqrMagnitude() const { return x() * x() + y() * y() + z() * z(); }
  inline Vector3Base normalized() const { return *this / magnitude(); }

  inline void normalize() { *this = normalized(); }

  inline T& x() { return elements_[0]; }
  inline T& y() { return elements_[1]; }
  inline T& z() { return elements_[2]; }
  inline const T& x() const { return elements_[0]; }
  inline const T& y() const { return elements_[1]; }
  inline const T& z() const { return elements_[2]; }

  static inline Vector3Base zero() { return Vector3Base(); }
  static inline Vector3Base one() {
    return Vector3Base(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1));
  }
  static inline Vector3Base forward() {
    return Vector3Base(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
  }
  static inline Vector3Base backward() {
    return Vector3Base(static_cast<T>(0), static_cast<T>(0),
                       static_cast<T>(-1));
  }
  static inline Vector3Base right() {
    return Vector3Base(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
  }
  static inline Vector3Base left() {
    return Vector3Base(static_cast<T>(-1), static_cast<T>(0),
                       static_cast<T>(0));
  }
  static inline Vector3Base up() {
    return Vector3Base(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
  }
  static inline Vector3Base down() {
    return Vector3Base(static_cast<T>(0), static_cast<T>(-1),
                       static_cast<T>(0));
  }

 private:
  T elements_[3];
};

template <typename T>
inline Bool operator==(const Vector3Base<T>& lhs, const Vector3Base<T>& rhs) {
  return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z();
}

template <typename T>
inline Bool operator!=(const Vector3Base<T>& lhs, const Vector3Base<T>& rhs) {
  return !(lhs == rhs);
}

template <typename T>
inline Vector3Base<T> operator+(const Vector3Base<T>& lhs,
                                const Vector3Base<T>& rhs) {
  auto r = lhs;
  return r += rhs;
}

template <typename T>
inline Vector3Base<T> operator-(const Vector3Base<T>& lhs,
                                const Vector3Base<T>& rhs) {
  auto r = lhs;
  return r -= rhs;
}

template <typename T, typename U>
inline Vector3Base<T> operator*(const Vector3Base<T>& lhs, U rhs) {
  auto r = lhs;
  return r *= rhs;
}

template <typename T, typename U>
inline Vector3Base<T> operator*(U lhs, const Vector3Base<T>& rhs) {
  return rhs * lhs;
}

template <typename T, typename U>
inline Vector3Base<T> operator/(const Vector3Base<T>& lhs, U rhs) {
  auto r = lhs;
  return r /= rhs;
}

template <typename T>
inline T angle(const Vector3Base<T>& lhs, const Vector3Base<T>& rhs) {
  return acos(dot(lhs, rhs) / (lhs.magnitude() * rhs.magnitude()));
}

template <typename T>
inline T distance(const Vector3Base<T>& lhs, const Vector3Base<T>& rhs) {
  return (lhs - rhs).magnitude();
}

template <typename T>
inline T dot(const Vector3Base<T>& lhs, const Vector3Base<T>& rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

template <typename T>
inline Vector3Base<T> cross(const Vector3Base<T>& lhs,
                            const Vector3Base<T>& rhs) {
  return Vector3Base<T>(lhs.y() * rhs.z() - lhs.z() * rhs.y(),
                        lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                        lhs.x() * rhs.y() - lhs.y() * rhs.x());
}

template <typename T>
inline Vector3Base<T> lerp(const Vector3Base<T>& a, const Vector3Base<T>& b,
                           T t) {
  return a * (static_cast<T>(1) - t) + b * t;
}

using Vector3 = Vector3Base<Float32>;
using Vector3F64 = Vector3Base<Float64>;

}  // namespace math
}  // namespace temp
