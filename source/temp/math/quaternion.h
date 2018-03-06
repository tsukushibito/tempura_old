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
    return angles;
  }

  Float32 magnitude() const { return element_.magnitude(); }
  Quaternion normalized() const {
    auto result = *this;
    result.element_.normalize();
    return result;
  }
  void normalize() { element_.normalize(); }
  Quaternion conjugate() const {
    return Quaternion(-element_.x(), -element_.y(), -element_.z(),
                      element_.w());
  }

  Matrix4x4 toMatrix() const {
    auto&& e = element_;
    return Matrix4x4(                               //
        1 - 2 * e.y() * e.y() - 2 * e.z() * e.z(),  // 00
        2 * e.x() * e.y() + 2 * e.w() * e.z(),      // 01
        2 * e.x() * e.z() - 2 * e.w() * e.y(),      // 02
        0,                                          // 03
        2 * e.x() * e.y() - 2 * e.w() * e.z(),      // 10
        1 - 2 * e.x() * e.x() - 2 * e.z() * e.z(),  // 11
        2 * e.y() * e.z() + 2 * e.w() * e.x(),      // 12
        0,                                          // 13
        2 * e.x() * e.z() + 2 * e.w() * e.y(),      // 20
        2 * e.y() * e.z() - 2 * e.w() * e.x(),      // 21
        1 - 2 * e.x() * e.x() - 2 * e.y() * e.y(),  // 22
        0,                                          // 23
        0, 0, 0, 1);
  }

  static inline Quaternion identity() {
    return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);
  }

 private:
  Vector4 element_;
};
}  // namespace math
}  // namespace temp
