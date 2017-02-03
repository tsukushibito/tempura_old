/**
 * @file matrix.h
 * @brief matrix
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-09-01
 */
#pragma once
#ifndef GUARD_b00e28b25c664a42adda994baba46c75
#define GUARD_b00e28b25c664a42adda994baba46c75

#include "temp/math/vector.h"
#include "temp/temp_assert.h"
#include "temp/type.h"

namespace temp {
namespace math {

class RowOrder {};
class ColOrder {};

// 演算子の前方宣言
template <typename T>
class Matrix44Base;
template <typename T>
Matrix44Base<T> operator*(const Matrix44Base<T>& lhs, Float32 rhs);
template <typename T>
Matrix44Base<T> operator*(Float32& lhs, const Matrix44Base<T>& rhs);
template <typename T>
Matrix44Base<T> operator/(const Matrix44Base<T>& lhs, Float32 rhs);
template <typename T>
Vector4Base<T> operator*(const Vector4Base<T>& lhs, const Matrix44Base<T>& rhs);
template <typename T>
Matrix44Base<T> operator*(const Matrix44Base<T>& lhs,
                          const Matrix44Base<T>& rhs);

// 4行4列行列
// 要素は列優先のメモリ配列
template <typename T>
class Matrix44Base {
public:
    using Vec4 = Vector4Base<T>;

    // デフォルトコンストラクタ
    Matrix44Base();

    // 要素を配列として受け取る
    Matrix44Base(T element[16]);

    // 行毎に初期化
    Matrix44Base(RowOrder, const Vec4& row0, const Vec4& row1, const Vec4& row2,
                 const Vec4& row3);

    // 列毎に初期化
    Matrix44Base(ColOrder, const Vec4& col0, const Vec4& col1, const Vec4& col2,
                 const Vec4& col3);

    // コピーコンストラクタ
    Matrix44Base(const Matrix44Base&) = default;
    // コピー代入演算子
    Matrix44Base& operator=(const Matrix44Base&) = default;

#if _MSC_VER < 1900
#else
    Matrix44Base(Matrix44Base&&) noexcept = default;
    Matrix44Base& operator=(Matrix44Base&&) noexcept = default;
#endif

    ~Matrix44Base() = default;

    String toString() const;

    Vector4Base<T>& operator[](Size index);
    const Vector4Base<T>& operator[](Size index) const;

    T operator()(Size row, Size col) const;

    Bool operator==(const Matrix44Base& rhs);
    Bool operator!=(const Matrix44Base& rhs);

    friend Matrix44Base operator*<T>(const Matrix44Base& lhs, Float32 rhs);
    friend Matrix44Base operator*<T>(Float32& lhs, const Matrix44Base& rhs);
    friend Matrix44Base operator/<T>(const Matrix44Base& lhs, Float32 rhs);
    friend Vector4Base<T> operator*<T>(const Vector4Base<T>& lhs,
                                       const Matrix44Base&   rhs);
    friend Matrix44Base operator*<T>(const Matrix44Base& lhs,
                                     const Matrix44Base& rhs);

    Float32                determinant() const;
    Optional<Matrix44Base> inverse() const;
    Matrix44Base           transpose() const;

private:
    Vector4Base<T> row(Size index) const;
    Vector4Base<T> cols_[4];

public:
    static const Matrix44Base kZero;
    static const Matrix44Base kIdentity;
};

using Matrix44     = Matrix44Base<Float32>;
using Matrix44UPtr = std::unique_ptr<Matrix44> using Matrix44SPtr
    = std::shared_ptr<Matrix44> using Matrix44WPtr = std::weak_ptr<Matrix44>

}  // namespace math
}  // namespace temp

#include "temp/math/matrix_detail.h"

#endif  // GUARD_b00e28b25c664a42adda994baba46c75
