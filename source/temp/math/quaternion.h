#pragma once
#include "temp/common/common.h"
#include "temp/math/vector4.h"

namespace temp {
namespace math {
class Quaternion {
 public:
  Quaternion() = default;
  explicit Quaternion(Float32 x, Float32 y, Float32 z, Float32 w)
      : element_(x, y, z, w) {
    normalize();
  }

  Quaternion(const Quaternion&) = default;
  Quaternion& operator=(const Quaternion&) = default;

  Quaternion& operator*=(const Quaternion& other) {
    auto&& q = *this;
    auto&& p = other;
    *this = Quaternion(                                                 //
        q.x() * p.w() + q.w() * p.x() - q.z() * p.y() + q.y() * p.z(),  //
        q.y() * p.w() + q.z() * p.x() + q.w() * p.y() - q.x() * p.z(),  //
        q.z() * p.w() - q.y() * p.x() + q.x() * p.y() + q.w() * p.z(),  //
        q.w() * p.w() - q.x() * p.x() - q.y() * p.y() - q.z() * p.z()   //
    );
    return *this;
  }

  Vector3 eulerAngles() const {
    Vector3 angles;
    auto mat = toMatrix();
    const Float32 threshold = 0.000001f;

    if (std::abs(mat(1, 2) + 1.0f) < threshold) {  // sin(x) == 1
      angles.x() = kPi_2;
      angles.y() = 0.0f;
      angles.z() = -std::atan2(mat(0, 1), mat(0, 0));
    } else if (std::abs(mat(1, 2) - 1.0f) < threshold) {  // sin(x) == -1
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

  Float32 magnitude() const { return element_.magnitude(); }
  Quaternion normalized() const {
    auto result = *this;
    result.element_.normalize();
    return result;
  }
  void normalize() { element_.normalize(); }
  Quaternion conjugate() const { return Quaternion(-x(), -y(), -z(), w()); }

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

  Float32& x() { return element_.x(); }
  Float32& y() { return element_.y(); }
  Float32& z() { return element_.z(); }
  Float32& w() { return element_.w(); }
  const Float32& x() const { return element_.x(); }
  const Float32& y() const { return element_.y(); }
  const Float32& z() const { return element_.z(); }
  const Float32& w() const { return element_.w(); }

  static inline Quaternion identity() {
    return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
  }

  static inline Quaternion fromXAxisAngle(Float32 deg) {
    auto rad = degreeToRadian(deg);
    auto angle = 0.5f * rad;
    return Quaternion(std::sin(angle), 0.0f, 0.0f, std::cos(angle));
  }

  static inline Quaternion fromYAxisAngle(Float32 deg) {
    auto rad = degreeToRadian(deg);
    auto angle = 0.5f * rad;
    return Quaternion(0.0f, std::sin(angle), 0.0f, std::cos(angle));
  }

  static inline Quaternion fromZAxisAngle(Float32 deg) {
    auto rad = degreeToRadian(deg);
    auto angle = 0.5f * rad;
    return Quaternion(0.0f, 0.0f, std::sin(angle), std::cos(angle));
  }

 private:
  Vector4 element_;
};

inline Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs) {
  auto result = lhs;
  return result *= rhs;
}

inline Vector3 operator*(const Quaternion& lhs, const Vector3& rhs) {
  auto pos = Quaternion(rhs.x(), rhs.y(), rhs.z(), 0.0f);
  auto r = lhs * pos * lhs.conjugate();
  return Vector3(r.x(), r.y(), r.z());
}
}  // namespace math
}  // namespace temp
