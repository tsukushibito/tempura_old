#pragma once
#include "temp/common/common.h"
#include "temp/math/vector3.h"

namespace temp {
namespace math {

// class Vector4;
// Bool operator==(const Vector4& lhs, const Vector4& rhs);
// Bool operator!=(const Vector4& lhs, const Vector4& rhs);
// Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
// Vector4 operator-(const Vector4& lhs, const Vector4& rhs);
// Vector4 operator*(const Vector4& lhs, Float32 rhs);
// Vector4 operator*(Float32 lhs, const Vector4& rhs);
// Vector4 operator/(const Vector4& lhs, Float32 rhs);
// Float32 dot(const Vector4& lhs, const Vector4& rhs);

template <typename T>
class Vector4Base {
 public:
  Vector4Base()
      : Vector4Base(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
                    static_cast<T>(0)) {}
  explicit Vector4Base(T x, T y, T z, T w) {
    elements_[0] = x, elements_[1] = y, elements_[2] = z, elements_[3] = w;
  }
  explicit Vector4Base(const Array<T, 4> e)
      : Vector4Base(e[0], e[1], e[2], e[3]) {}
  explicit Vector4Base(const Vector3Base<T>& vec3, T w = static_cast<T>(0))
      : Vector4Base(vec3.x(), vec3.y(), vec3.z(), w) {}
  Vector4Base(const Vector4Base&) = default;
  Vector4Base& operator=(const Vector4Base&) = default;
  ~Vector4Base() = default;

  inline operator Vector3Base<T>() const {
    return Vector3Base<T>(x(), y(), z());
  }
  inline T& operator[](Size i) { return elements_[i]; }
  inline const T& operator[](Size i) const { return elements_[i]; }

  inline Vector4Base& operator+=(const Vector4Base& rhs) {
    for (int i = 0; i < 4; ++i) {
      elements_[i] += rhs.elements_[i];
    }
    return *this;
  }

  inline Vector4Base& operator-=(const Vector4Base& rhs) {
    for (int i = 0; i < 4; ++i) {
      elements_[i] -= rhs.elements_[i];
    }
    return *this;
  }

  template <typename U>
  inline Vector4Base& operator*=(U scalar) {
    for (int i = 0; i < 4; ++i) {
      elements_[i] *= scalar;
    }
    return *this;
  }

  template <typename U>
  inline Vector4Base& operator/=(U scalar) {
    for (int i = 0; i < 4; ++i) {
      elements_[i] /= scalar;
    }
    return *this;
  }

  inline T magnitude() const { return std::sqrt(sqrMagnitude()); }
  inline T sqrMagnitude() const {
    return x() * x() + y() * y() + z() * z() + w() * w();
  }
  inline Vector4Base normalized() const { return *this / magnitude(); }

  inline void normalize() { *this = normalized(); }

  inline T& x() { return elements_[0]; }
  inline T& y() { return elements_[1]; }
  inline T& z() { return elements_[2]; }
  inline T& w() { return elements_[3]; }
  inline const T& x() const { return elements_[0]; }
  inline const T& y() const { return elements_[1]; }
  inline const T& z() const { return elements_[2]; }
  inline const T& w() const { return elements_[3]; }

  static inline Vector4Base zero() { return Vector4Base(); }
  static inline Vector4Base one() {
    return Vector4Base(static_cast<T>(1), static_cast<T>(1), static_cast<T>(1),
                       static_cast<T>(1));
  }

 private:
  T elements_[4];
};

template <typename T>
inline Bool operator==(const Vector4Base<T>& lhs, const Vector4Base<T>& rhs) {
  return lhs.x() == rhs.x() && lhs.y() == rhs.y() && lhs.z() == rhs.z() &&
         lhs.w() == rhs.w();
}

template <typename T>
inline Bool operator!=(const Vector4Base<T>& lhs, const Vector4Base<T>& rhs) {
  return !(lhs == rhs);
}

template <typename T>
inline Vector4Base<T> operator+(const Vector4Base<T>& lhs,
                                const Vector4Base<T>& rhs) {
  auto r = lhs;
  return r += rhs;
}

template <typename T>
inline Vector4Base<T> operator-(const Vector4Base<T>& lhs,
                                const Vector4Base<T>& rhs) {
  auto r = lhs;
  return r -= rhs;
}

template <typename T, typename U>
inline Vector4Base<T> operator*(const Vector4Base<T>& lhs, U rhs) {
  auto r = lhs;
  return r *= rhs;
}

template <typename T, typename U>
inline Vector4Base<T> operator*(U lhs, const Vector4Base<T>& rhs) {
  return rhs * lhs;
}

template <typename T, typename U>
inline Vector4Base<T> operator/(const Vector4Base<T>& lhs, U rhs) {
  auto r = lhs;
  return r /= rhs;
}

template <typename T>
inline T dot(const Vector4Base<T>& lhs, const Vector4Base<T>& rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z() +
         lhs.w() * rhs.w();
}

using Vector4 = Vector4Base<Float32>;
using Vector4F64 = Vector4Base<Float64>;

}  // namespace math
}  // namespace temp
