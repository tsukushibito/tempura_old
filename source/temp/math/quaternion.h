#pragma once
#include "temp/common/common.h"
#include "temp/math/vector4.h"

namespace temp {
namespace math {

template <typename T>
class QuaternionBase {
 public:
  QuaternionBase() = default;
  explicit QuaternionBase(T x, T y, T z, T w) : element_(x, y, z, w) {
    normalize();
  }

  QuaternionBase(const QuaternionBase&) = default;
  QuaternionBase& operator=(const QuaternionBase&) = default;

  QuaternionBase& operator*=(const QuaternionBase& other) {
    auto&& q = *this;
    auto&& p = other;
    *this = QuaternionBase(                                             //
        q.x() * p.w() + q.w() * p.x() - q.z() * p.y() + q.y() * p.z(),  //
        q.y() * p.w() + q.z() * p.x() + q.w() * p.y() - q.x() * p.z(),  //
        q.z() * p.w() - q.y() * p.x() + q.x() * p.y() + q.w() * p.z(),  //
        q.w() * p.w() - q.x() * p.x() - q.y() * p.y() - q.z() * p.z()   //
    );
    return *this;
  }

  Vector3Base<T> eulerAngles() const {
    Vector3Base<T> angles;
    auto mat = toMatrix();
    const T threshold = static_cast<T>(0.000001);

    if (std::abs(mat(1, 2) + static_cast<T>(1)) < threshold) {  // sin(x) == 1
      angles.x() = kPi_2;
      angles.y() = 0.0f;
      angles.z() = -std::atan2(mat(0, 1), mat(0, 0));
    } else if (std::abs(mat(1, 2) - static_cast<T>(1)) < threshold) {  // sin(x) == -1
      angles.x() = -kPi_2;
      angles.y() = 0.0f;
      angles.z() = -std::atan2(mat(0, 1), mat(0, 0));
    } else {
      angles.x() = -std::asin(mat(1, 2));
      angles.y() = std::atan2(mat(2, 2), mat(0, 2));
      angles.z() = std::atan2(mat(1, 1), mat(1, 0));
    }

    angles.x() = radianToDegree(2 * angles.x());
    angles.y() = radianToDegree(2 * angles.y());
    angles.z() = radianToDegree(2 * angles.z());
    return angles;
  }

  T magnitude() const { return element_.magnitude(); }
  QuaternionBase normalized() const {
    auto result = *this;
    result.element_.normalize();
    return result;
  }
  void normalize() { element_.normalize(); }
  QuaternionBase conjugate() const {
    return QuaternionBase(-x(), -y(), -z(), w());
  }

  Matrix4x4 toMatrix() const {
    auto c = conjugate();
    return Matrix4x4(                               //
        1 - 2 * c.y() * c.y() - 2 * c.z() * c.z(),  // 00
        2 * c.x() * c.y() + 2 * c.w() * c.z(),      // 01
        2 * c.x() * c.z() - 2 * c.w() * c.y(),      // 02
        0,                                          // 03
        2 * c.x() * c.y() - 2 * c.w() * c.z(),      // 10
        1 - 2 * c.x() * c.x() - 2 * c.z() * c.z(),  // 11
        2 * c.y() * c.z() + 2 * c.w() * c.x(),      // 12
        0,                                          // 13
        2 * c.x() * c.z() + 2 * c.w() * c.y(),      // 20
        2 * c.y() * c.z() - 2 * c.w() * c.x(),      // 21
        1 - 2 * c.x() * c.x() - 2 * c.y() * c.y(),  // 22
        0,                                          // 23
        0, 0, 0, 1);
  }

  inline T& x() { return element_.x(); }
  inline T& y() { return element_.y(); }
  inline T& z() { return element_.z(); }
  inline T& w() { return element_.w(); }
  inline const T& x() const { return element_.x(); }
  inline const T& y() const { return element_.y(); }
  inline const T& z() const { return element_.z(); }
  inline const T& w() const { return element_.w(); }

  static inline QuaternionBase identity() {
    return QuaternionBase(static_cast<T>(0), static_cast<T>(0),
                          static_cast<T>(0), static_cast<T>(1));
  }

  template <typename U>
  static inline QuaternionBase fromXAxisAngle(U deg) {
    auto rad = degreeToRadian(static_cast<Float32>(deg));
    auto angle = 0.5f * rad;
    return QuaternionBase(std::sin(angle), 0.0f, 0.0f, std::cos(angle));
  }

  template <typename U>
  static inline QuaternionBase fromYAxisAngle(U deg) {
    auto rad = degreeToRadian(static_cast<Float32>(deg));
    auto angle = 0.5f * rad;
    return QuaternionBase(0.0f, std::sin(angle), 0.0f, std::cos(angle));
  }

  template <typename U>
  static inline QuaternionBase fromZAxisAngle(U deg) {
    auto rad = degreeToRadian(static_cast<Float32>(deg));
    auto angle = 0.5f * rad;
    return QuaternionBase(0.0f, 0.0f, std::sin(angle), std::cos(angle));
  }

 private:
  Vector4Base<T> element_;
};

template <typename T>
inline QuaternionBase<T> operator*(const QuaternionBase<T>& lhs,
                                   const QuaternionBase<T>& rhs) {
  auto result = lhs;
  return result *= rhs;
}

template <typename T>
inline Vector3Base<T> operator*(const QuaternionBase<T>& lhs,
                                const Vector3Base<T>& rhs) {
  auto pos = QuaternionBase<T>(rhs.x(), rhs.y(), rhs.z(), static_cast<T>(0));
  auto r = lhs * pos * lhs.conjugate();
  return Vector3Base<T>(r.x(), r.y(), r.z());
}

using Quaternion = QuaternionBase<Float32>;
using QuaternionF64 = QuaternionBase<Float64>;
}  // namespace math
}  // namespace temp
