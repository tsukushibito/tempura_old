#pragma once
#include "temp/common/common.h"
#include "temp/math/vector4.h"

namespace temp {
namespace math {

class Matrix4x4 {
 public:
  Matrix4x4() : Matrix4x4(Vector4(), Vector4(), Vector4(), Vector4()) {}
  explicit Matrix4x4(const Vector4& row0, const Vector4& row1,
                     const Vector4& row2, const Vector4& row3) {
    rows_[0] = row0;
    rows_[1] = row1;
    rows_[2] = row2;
    rows_[3] = row3;
  }
  explicit Matrix4x4(const Array<Vector4, 4> rows) {
    rows_[0] = rows[0];
    rows_[1] = rows[1];
    rows_[2] = rows[2];
    rows_[3] = rows[3];
  }

  explicit Matrix4x4(Float32 _00, Float32 _01, Float32 _02, Float32 _03,
                     Float32 _10, Float32 _11, Float32 _12, Float32 _13,
                     Float32 _20, Float32 _21, Float32 _22, Float32 _23,
                     Float32 _30, Float32 _31, Float32 _32, Float32 _33)
      : Matrix4x4(Vector4(_00, _01, _02, _03), Vector4(_10, _11, _12, _13),
                  Vector4(_20, _21, _22, _23), Vector4(_30, _31, _32, _33)) {}

  explicit Matrix4x4(const Array<Float32, 16> e)
      : Matrix4x4(Vector4(e[0], e[1], e[2], e[3]),
                  Vector4(e[4], e[5], e[6], e[7]),
                  Vector4(e[8], e[9], e[10], e[11]),
                  Vector4(e[12], e[13], e[14], e[15])) {}

  Matrix4x4(const Matrix4x4&) = default;
  Matrix4x4& operator=(const Matrix4x4&) = default;

  Vector4& operator[](Size i) { return rows_[i]; }
  const Vector4& operator[](Size i) const { return rows_[i]; }
  Float32& operator()(Size r, Size c) { return rows_[r][c]; }
  const Float32& operator()(Size r, Size c) const { return rows_[r][c]; }

  Matrix4x4& operator+=(const Matrix4x4& other) {
    for (int r = 0; r < 4; ++r) {
      rows_[r] += other.rows_[r];
    }
    return *this;
  }

  Matrix4x4& operator-=(const Matrix4x4& other) {
    for (int r = 0; r < 4; ++r) {
      rows_[r] -= other.rows_[r];
    }
    return *this;
  }

  Matrix4x4& operator*=(const Matrix4x4& other) {
    for (int r = 0; r < 4; ++r) {
      auto temp = rows_[r];
      for (int c = 0; c < 4; ++c) {
        rows_[r][c] = dot(
            temp, Vector4(other(c, 0), other(c, 1), other(c, 2), other(c, 3)));
      }
    }
    return *this;
  }

  Matrix4x4& operator*=(Float32 scalar) {
    for (int r = 0; r < 4; ++r) {
      rows_[r] *= scalar;
    }
    return *this;
  }

  Matrix4x4& operator/=(Float32 scalar) {
    for (int r = 0; r < 4; ++r) {
      rows_[r] /= scalar;
    }
    return *this;
  }

  Float32 determinant() const;
  Matrix4x4 inversed() const;
  void inverse() { *this = inversed(); }

  Matrix4x4 transposed() const {
    return Matrix4x4(col(0), col(1), col(2), col(3));
  }
  void transpose() { *this = transposed(); }

  Vector4 row(Size i) const { return rows_[i]; }
  Vector4 col(Size i) const {
    return Vector4(rows_[0][i], rows_[1][i], rows_[2][i], rows_[3][i]);
  }

  static inline Matrix4x4 zero() { return Matrix4x4(); }

  static inline Matrix4x4 identity() {
    return Matrix4x4(
        Vector4(1.0f, 0.0f, 0.0f, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 0.0f),
        Vector4(0.0f, 0.0f, 1.0f, 0.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f));
  }

  static inline Matrix4x4 perspectiveFov(Float32 fov_y_degree, Float32 aspect,
                                         Float32 znear, Float32 zfar) {
    auto fov_y_rad = degreeToRadian(fov_y_degree);
    auto scale_y = 1.0f / std::tan(fov_y_rad / 2.0f);
    auto scale_x = scale_y / aspect;
    return Matrix4x4(                                                         //
        scale_x, 0.0f, 0.0f, 0.0f,                                            //
        0.0f, scale_y, 0.0f, 0.0f,                                            //
        0.0f, 0.0f, zfar / (zfar - znear), -(znear * zfar) / (zfar - znear),  //
        0.0f, 0.0f, 1.0f, 0.0f);
  }

  static inline Matrix4x4 perspectiveFovReversedZ(Float32 fov_y_degree,
                                                  Float32 aspect, Float32 znear,
                                                  Float32 zfar) {
    auto fov_y_rad = degreeToRadian(fov_y_degree);
    auto scale_y = 1.0f / std::tan(fov_y_rad / 2.0f);
    auto scale_x = scale_y / aspect;
    return Matrix4x4(               //
        scale_x, 0.0f, 0.0f, 0.0f,  //
        0.0f, scale_y, 0.0f, 0.0f,  //
        0.0f, 0.0f, -(zfar / (zfar - znear)) - 1.0f,
        (znear * zfar) / (zfar - znear),  //
        0.0f, 0.0f, 1.0f, 0.0f);
  }

 private:
  Vector4 rows_[4];
};

inline Bool operator==(const Matrix4x4& lhs, const Matrix4x4& rhs) {
  return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] &&
         lhs[3] == rhs[3];
}

inline Bool operator!=(const Matrix4x4& lhs, const Matrix4x4& rhs) {
  return !(lhs == rhs);
}

inline Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4& rhs) {
  auto result = lhs;
  return result += rhs;
}

inline Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4& rhs) {
  auto result = lhs;
  return result -= rhs;
}

inline Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs) {
  auto result = lhs;
  return result *= rhs;
}

inline Matrix4x4 operator*(Float32 lhs, const Matrix4x4& rhs) {
  auto result = rhs;
  return result *= lhs;
}

inline Matrix4x4 operator*(const Matrix4x4& lhs, Float32 rhs) {
  return rhs * lhs;
}

inline Vector4 operator*(const Matrix4x4& lhs, const Vector4& rhs) {
  return Vector4(dot(lhs[0], rhs), dot(lhs[1], rhs), dot(lhs[2], rhs),
                 dot(lhs[3], rhs));
}

inline Matrix4x4 operator/(const Matrix4x4& lhs, Float32 rhs) {
  auto result = lhs;
  return result /= rhs;
}
}  // namespace math
}  // namespace temp

#include "temp/math/detail/matrix4x4_detail.h"