#pragma once
#include "temp/common/common.h"
#include "temp/math/vector4.h"

namespace temp {
namespace math {

template <typename T>
class Matrix4x4Base {
 public:
  Matrix4x4Base()
      : Matrix4x4Base(Vector4Base<T>(), Vector4Base<T>(),
                      Vector4Base<T>(), Vector4Base<T>()) {}
  explicit Matrix4x4Base(const Vector4Base<T>& row0, const Vector4Base<T>& row1,
                         const Vector4Base<T>& row2,
                         const Vector4Base<T>& row3) {
    rows_[0] = row0;
    rows_[1] = row1;
    rows_[2] = row2;
    rows_[3] = row3;
  }
  explicit Matrix4x4Base(const Array<Vector4Base<T>, 4> rows) {
    rows_[0] = rows[0];
    rows_[1] = rows[1];
    rows_[2] = rows[2];
    rows_[3] = rows[3];
  }

  explicit Matrix4x4Base(T _00, T _01, T _02, T _03, T _10, T _11, T _12, T _13,
                         T _20, T _21, T _22, T _23, T _30, T _31, T _32, T _33)
      : Matrix4x4Base(Vector4Base<T>(_00, _01, _02, _03),
                      Vector4Base<T>(_10, _11, _12, _13),
                      Vector4Base<T>(_20, _21, _22, _23),
                      Vector4Base<T>(_30, _31, _32, _33)) {}

  explicit Matrix4x4Base(const Array<T, 16> e)
      : Matrix4x4Base(Vector4Base<T>(e[0], e[1], e[2], e[3]),
                      Vector4Base<T>(e[4], e[5], e[6], e[7]),
                      Vector4Base<T>(e[8], e[9], e[10], e[11]),
                      Vector4Base<T>(e[12], e[13], e[14], e[15])) {}

  Matrix4x4Base(const Matrix4x4Base&) = default;
  Matrix4x4Base& operator=(const Matrix4x4Base&) = default;

  inline Vector4Base<T>& operator[](Size i) { return rows_[i]; }
  inline const Vector4Base<T>& operator[](Size i) const { return rows_[i]; }
  inline T& operator()(Size r, Size c) { return rows_[r][c]; }
  inline const T& operator()(Size r, Size c) const { return rows_[r][c]; }

  Matrix4x4Base& operator+=(const Matrix4x4Base& other) {
    for (int r = 0; r < 4; ++r) {
      rows_[r] += other.rows_[r];
    }
    return *this;
  }

  Matrix4x4Base& operator-=(const Matrix4x4Base& other) {
    for (int r = 0; r < 4; ++r) {
      rows_[r] -= other.rows_[r];
    }
    return *this;
  }

  Matrix4x4Base& operator*=(const Matrix4x4Base& other) {
    for (int r = 0; r < 4; ++r) {
      auto temp = rows_[r];
      for (int c = 0; c < 4; ++c) {
        rows_[r][c] = dot(
            temp, Vector4(other(c, 0), other(c, 1), other(c, 2), other(c, 3)));
      }
    }
    return *this;
  }

  template <typename U>
  Matrix4x4Base& operator*=(U scalar) {
    for (int r = 0; r < 4; ++r) {
      rows_[r] *= scalar;
    }
    return *this;
  }

  template <typename U>
  Matrix4x4Base& operator/=(U scalar) {
    for (int r = 0; r < 4; ++r) {
      rows_[r] /= scalar;
    }
    return *this;
  }

  T determinant() const;
  Matrix4x4Base inversed() const;
  void inverse() { *this = inversed(); }

  Matrix4x4Base transposed() const {
    return Matrix4x4Base(col(0), col(1), col(2), col(3));
  }
  void transpose() { *this = transposed(); }

  Vector4Base<T> row(Size i) const { return rows_[i]; }
  Vector4Base<T> col(Size i) const {
    return Vector4(rows_[0][i], rows_[1][i], rows_[2][i], rows_[3][i]);
  }

  static inline Matrix4x4Base zero() { return Matrix4x4Base(); }

  static inline Matrix4x4Base identity() {
    return Matrix4x4Base(  //
        Vector4Base<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0),
                       static_cast<T>(0)),
        Vector4Base<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0),
                       static_cast<T>(0)),
        Vector4Base<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1),
                       static_cast<T>(0)),
        Vector4Base<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0),
                       static_cast<T>(1)));
  }

  static inline Matrix4x4Base perspectiveFov(T fov_y_degree, T aspect, T znear,
                                             T zfar) {
    auto fov_y_rad = degreeToRadian(fov_y_degree);
    auto scale_y = 1.0f / std::tan(fov_y_rad / 2.0f);
    auto scale_x = scale_y / aspect;
    return Matrix4x4Base(                                               //
        scale_x, 0, 0, 0,                                               //
        0, scale_y, 0, 0,                                               //
        0, 0, zfar / (zfar - znear), -(znear * zfar) / (zfar - znear),  //
        0, 0, 1, 0);
  }

  static inline Matrix4x4Base perspectiveFovReversedZ(T fov_y_degree, T aspect,
                                                      T znear, T zfar) {
    auto fov_y_rad = degreeToRadian(fov_y_degree);
    auto scale_y = 1.0f / std::tan(fov_y_rad / 2.0f);
    auto scale_x = scale_y / aspect;
    return Matrix4x4Base(  //
        scale_x, 0, 0, 0,  //
        0, scale_y, 0, 0,  //
        0, 0, -(zfar / (zfar - znear)) - 1,
        (znear * zfar) / (zfar - znear),  //
        0, 0, 1, 0);
  }

 private:
  Vector4Base<T> rows_[4];
};

template <typename T>
T Matrix4x4Base<T>::determinant() const {
  auto&& self = *this;
  T d;
  d = self(0, 0) * self(1, 1) * self(2, 2) * self(3, 3) +  //
      self(0, 0) * self(1, 2) * self(2, 3) * self(3, 1) +  //
      self(0, 0) * self(1, 3) * self(2, 1) * self(3, 2) -  //

      self(0, 0) * self(1, 3) * self(2, 2) * self(3, 1) -  //
      self(0, 0) * self(1, 2) * self(2, 1) * self(3, 3) -  //
      self(0, 0) * self(1, 1) * self(2, 3) * self(3, 2) -  //

      self(0, 1) * self(1, 0) * self(2, 2) * self(3, 3) -  //
      self(0, 2) * self(1, 0) * self(2, 3) * self(3, 1) -  //
      self(0, 3) * self(1, 0) * self(2, 1) * self(3, 2) +  //

      self(0, 3) * self(1, 0) * self(2, 2) * self(3, 1) +  //
      self(0, 2) * self(1, 0) * self(2, 1) * self(3, 3) +  //
      self(0, 1) * self(1, 0) * self(2, 3) * self(3, 2) +  //

      self(0, 1) * self(1, 2) * self(2, 0) * self(3, 3) +  //
      self(0, 2) * self(1, 3) * self(2, 0) * self(3, 1) +  //
      self(0, 3) * self(1, 1) * self(2, 0) * self(3, 2) -  //

      self(0, 3) * self(1, 2) * self(2, 0) * self(3, 1) -  //
      self(0, 2) * self(1, 1) * self(2, 0) * self(3, 3) -  //
      self(0, 1) * self(1, 3) * self(2, 0) * self(3, 2) -  //

      self(0, 1) * self(1, 2) * self(2, 3) * self(3, 0) -  //
      self(0, 2) * self(1, 3) * self(2, 1) * self(3, 0) -  //
      self(0, 3) * self(1, 1) * self(2, 2) * self(3, 0) +  //

      self(0, 3) * self(1, 2) * self(2, 1) * self(3, 0) +  //
      self(0, 2) * self(1, 1) * self(2, 3) * self(3, 0) +  //
      self(0, 1) * self(1, 3) * self(2, 2) * self(3, 0);   //
  return d;
}

template <typename T>
Matrix4x4Base<T> Matrix4x4Base<T>::inversed() const {
  auto d = determinant();
  auto&& m = *this;

  auto _00 = (+m(1, 1) * m(2, 2) * m(3, 3)    //
              + m(1, 2) * m(2, 3) * m(3, 1)   //
              + m(1, 3) * m(2, 1) * m(3, 2)   //
              - m(1, 3) * m(2, 2) * m(3, 1)   //
              - m(1, 2) * m(2, 1) * m(3, 3)   //
              - m(1, 1) * m(2, 3) * m(3, 2))  //
             / d;

  auto _01 = (-m(0, 1) * m(2, 2) * m(3, 3)    //
              - m(0, 2) * m(2, 3) * m(3, 1)   //
              - m(0, 3) * m(2, 1) * m(3, 2)   //
              + m(0, 3) * m(2, 2) * m(3, 1)   //
              + m(0, 2) * m(2, 1) * m(3, 3)   //
              + m(0, 1) * m(2, 3) * m(3, 2))  //
             / d;

  auto _02 = (+m(0, 1) * m(1, 2) * m(3, 3)    //
              + m(0, 2) * m(1, 3) * m(3, 1)   //
              + m(0, 3) * m(1, 1) * m(3, 2)   //
              - m(0, 3) * m(1, 2) * m(3, 1)   //
              - m(0, 2) * m(1, 1) * m(3, 3)   //
              - m(0, 1) * m(1, 3) * m(3, 2))  //
             / d;

  auto _03 = (-m(0, 1) * m(1, 2) * m(2, 3)    //
              - m(0, 2) * m(1, 3) * m(2, 1)   //
              - m(0, 3) * m(1, 1) * m(2, 2)   //
              + m(0, 3) * m(1, 2) * m(2, 1)   //
              + m(0, 2) * m(1, 1) * m(2, 3)   //
              + m(0, 1) * m(1, 3) * m(2, 2))  //
             / d;

  auto _10 = (-m(1, 0) * m(2, 2) * m(3, 3)    //
              - m(1, 2) * m(2, 3) * m(3, 0)   //
              - m(1, 3) * m(2, 0) * m(3, 2)   //
              + m(1, 3) * m(2, 2) * m(3, 0)   //
              + m(1, 2) * m(2, 0) * m(3, 3)   //
              + m(1, 0) * m(2, 3) * m(3, 2))  //
             / d;

  auto _11 = (+m(0, 0) * m(2, 2) * m(3, 3)    //
              + m(0, 2) * m(2, 3) * m(3, 0)   //
              + m(0, 3) * m(2, 0) * m(3, 2)   //
              - m(0, 3) * m(2, 2) * m(3, 0)   //
              - m(0, 2) * m(2, 0) * m(3, 3)   //
              - m(0, 0) * m(2, 3) * m(3, 2))  //
             / d;

  auto _12 = (-m(0, 0) * m(1, 2) * m(3, 3)    //
              - m(0, 2) * m(1, 3) * m(3, 0)   //
              - m(0, 3) * m(1, 0) * m(3, 2)   //
              + m(0, 3) * m(1, 2) * m(3, 0)   //
              + m(0, 2) * m(1, 0) * m(3, 3)   //
              + m(0, 0) * m(1, 3) * m(3, 2))  //
             / d;

  auto _13 = (+m(0, 0) * m(1, 2) * m(2, 3)    //
              + m(0, 2) * m(1, 3) * m(2, 0)   //
              + m(0, 3) * m(1, 0) * m(2, 2)   //
              - m(0, 3) * m(1, 2) * m(2, 0)   //
              - m(0, 2) * m(1, 0) * m(2, 3)   //
              - m(0, 0) * m(1, 3) * m(2, 2))  //
             / d;

  auto _20 = (+m(1, 0) * m(2, 1) * m(3, 3)    //
              + m(1, 1) * m(2, 3) * m(3, 0)   //
              + m(1, 3) * m(2, 0) * m(3, 1)   //
              - m(1, 3) * m(2, 1) * m(3, 0)   //
              - m(1, 1) * m(2, 0) * m(3, 3)   //
              - m(1, 0) * m(2, 3) * m(3, 1))  //
             / d;

  auto _21 = (-m(0, 0) * m(2, 1) * m(3, 3)    //
              - m(0, 1) * m(2, 3) * m(3, 0)   //
              - m(0, 3) * m(2, 0) * m(3, 1)   //
              + m(0, 3) * m(2, 1) * m(3, 0)   //
              + m(0, 1) * m(2, 0) * m(3, 3)   //
              + m(0, 0) * m(2, 3) * m(3, 1))  //
             / d;

  auto _22 = (+m(0, 0) * m(1, 1) * m(3, 3)    //
              + m(0, 1) * m(1, 3) * m(3, 0)   //
              + m(0, 3) * m(1, 0) * m(3, 1)   //
              - m(0, 3) * m(1, 1) * m(3, 0)   //
              - m(0, 1) * m(1, 0) * m(3, 3)   //
              - m(0, 0) * m(1, 3) * m(3, 1))  //
             / d;

  auto _23 = (-m(0, 0) * m(1, 1) * m(2, 3)    //
              - m(0, 1) * m(1, 3) * m(2, 0)   //
              - m(0, 3) * m(1, 0) * m(2, 1)   //
              + m(0, 3) * m(1, 1) * m(2, 0)   //
              + m(0, 1) * m(1, 0) * m(2, 3)   //
              + m(0, 0) * m(1, 3) * m(2, 1))  //
             / d;

  auto _30 = (-m(1, 0) * m(2, 1) * m(3, 2)    //
              - m(1, 1) * m(2, 2) * m(3, 0)   //
              - m(1, 2) * m(2, 0) * m(3, 1)   //
              + m(1, 2) * m(2, 1) * m(3, 0)   //
              + m(1, 1) * m(2, 0) * m(3, 2)   //
              + m(1, 0) * m(2, 2) * m(3, 1))  //
             / d;

  auto _31 = (+m(0, 0) * m(2, 1) * m(3, 2)    //
              + m(0, 1) * m(2, 2) * m(3, 0)   //
              + m(0, 2) * m(2, 0) * m(3, 1)   //
              - m(0, 2) * m(2, 1) * m(3, 0)   //
              - m(0, 1) * m(2, 0) * m(3, 2)   //
              - m(0, 0) * m(2, 2) * m(3, 1))  //
             / d;

  auto _32 = (-m(0, 0) * m(1, 1) * m(3, 2)    //
              - m(0, 1) * m(1, 2) * m(3, 0)   //
              - m(0, 2) * m(1, 0) * m(3, 1)   //
              + m(0, 2) * m(1, 1) * m(3, 0)   //
              + m(0, 1) * m(1, 0) * m(3, 2)   //
              + m(0, 0) * m(1, 2) * m(3, 1))  //
             / d;

  auto _33 = (+m(0, 0) * m(1, 1) * m(2, 2)    //
              + m(0, 1) * m(1, 2) * m(2, 0)   //
              + m(0, 2) * m(1, 0) * m(2, 1)   //
              - m(0, 2) * m(1, 1) * m(2, 0)   //
              - m(0, 1) * m(1, 0) * m(2, 2)   //
              - m(0, 0) * m(1, 2) * m(2, 1))  //
             / d;

  return Matrix4x4Base(_00, _01, _02, _03,  //
                   _10, _11, _12, _13,  //
                   _20, _21, _22, _23,  //
                   _30, _31, _32, _33);
}

template <typename T>
inline Bool operator==(const Matrix4x4Base<T>& lhs,
                       const Matrix4x4Base<T>& rhs) {
  return lhs[0] == rhs[0] && lhs[1] == rhs[1] && lhs[2] == rhs[2] &&
         lhs[3] == rhs[3];
}

template <typename T>
inline Bool operator!=(const Matrix4x4Base<T>& lhs,
                       const Matrix4x4Base<T>& rhs) {
  return !(lhs == rhs);
}

template <typename T>
inline Matrix4x4Base<T> operator+(const Matrix4x4Base<T>& lhs,
                                  const Matrix4x4Base<T>& rhs) {
  auto result = lhs;
  return result += rhs;
}

template <typename T>
inline Matrix4x4Base<T> operator-(const Matrix4x4Base<T>& lhs,
                                  const Matrix4x4Base<T>& rhs) {
  auto result = lhs;
  return result -= rhs;
}

template <typename T>
inline Matrix4x4Base<T> operator*(const Matrix4x4Base<T>& lhs,
                                  const Matrix4x4Base<T>& rhs) {
  auto result = lhs;
  return result *= rhs;
}

template <typename T, typename U>
inline Matrix4x4Base<T> operator*(U lhs, const Matrix4x4Base<T>& rhs) {
  auto result = rhs;
  return result *= lhs;
}

template <typename T, typename U>
inline Matrix4x4Base<T> operator*(const Matrix4x4Base<T>& lhs, U rhs) {
  return rhs * lhs;
}

template <typename T>
inline Vector4Base<T> operator*(const Matrix4x4Base<T>& lhs,
                                const Vector4Base<T>& rhs) {
  return Vector4Base<T>(dot(lhs[0], rhs), dot(lhs[1], rhs), dot(lhs[2], rhs),
                        dot(lhs[3], rhs));
}

template <typename T, typename U>
inline Matrix4x4Base<T> operator/(const Matrix4x4Base<T>& lhs, U rhs) {
  auto result = lhs;
  return result /= rhs;
}

using Matrix4x4 = Matrix4x4Base<Float32>;
using Matrix4x4F64 = Matrix4x4Base<Float64>;

}  // namespace math
}  // namespace temp
