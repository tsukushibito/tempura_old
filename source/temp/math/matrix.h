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

#include "temp/type.h"
#include "temp/temp_assert.h"
#include "temp/math/vector.h"

namespace temp {
namespace math {

template<typename T>
class Matrix44Base;
template<typename T>
Matrix44Base<T> operator*(const Matrix44Base<T> &lhs, Float32 rhs);
template<typename T>
Matrix44Base<T> operator*(Float32 &lhs, const Matrix44Base<T> &rhs);
template<typename T>
Matrix44Base<T> operator/(const Matrix44Base<T> &lhs, Float32 rhs);
template<typename T> 
Vector4Base<T> operator*(const Vector4Base<T> &lhs, const Matrix44Base<T> &rhs);
template<typename T> 
Matrix44Base<T> operator*(const Matrix44Base<T> &lhs, const Matrix44Base<T> &rhs);
    
template<typename T> 
class Matrix44Base {
public:
    Matrix44Base();

    Matrix44Base(
            T _11, T _21, T _31, T _41, 
            T _12, T _22, T _32, T _42, 
            T _13, T _23, T _33, T _43, 
            T _14, T _24, T _34, T _44);

    Matrix44Base(
            const Vector4Base<T> &col1, 
            const Vector4Base<T> &col2, 
            const Vector4Base<T> &col3, 
            const Vector4Base<T> &col4);

    Matrix44Base(const Matrix44Base &) = default;
    Matrix44Base &operator=(const Matrix44Base &) = default;

    Matrix44Base(Matrix44Base &&) noexcept = default;
    Matrix44Base &operator=(Matrix44Base &&) noexcept = default;

    ~Matrix44Base() = default;

    String toString() const;

    T *operator[](Size index);
    const T *operator[](Size index) const;

    Bool operator==(const Matrix44Base &rhs);
    Bool operator!=(const Matrix44Base &rhs);

    friend Matrix44Base operator*< T >(const Matrix44Base &lhs, Float32 rhs);
    friend Matrix44Base operator*< T >(Float32 &lhs, const Matrix44Base &rhs);
    friend Matrix44Base operator/< T >(const Matrix44Base &lhs, Float32 rhs);
    friend Vector4Base<T> operator*< T >(const Vector4Base<T> &lhs, const Matrix44Base &rhs);
    friend Matrix44Base operator*< T >(const Matrix44Base &lhs, const Matrix44Base &rhs);
    
    Float32 determinant() const;
    Optional<Matrix44Base> inverse() const;
    Matrix44Base transpose() const;
private:
    union {
        T m_[4][4];
        Vector4Base<T> col_[4];
    };

    Vector4Base<T> row(Size index) const;

public:
    static const Matrix44Base kZero;
    static const Matrix44Base kIdentity;
};
    
using Matrix44 = Matrix44Base<Float32>;
    
} // namespace math
} // namespace temp

#include "temp/math/matrix_detail.h"

#endif // GUARD_b00e28b25c664a42adda994baba46c75
