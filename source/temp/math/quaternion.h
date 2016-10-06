/**
 * @file quaternion.h
 * @brief quaternion
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-09-01
 */
#pragma once
#ifndef GUARD_310e3077c88749ee91ab93a6d1303417
#define GUARD_310e3077c88749ee91ab93a6d1303417

#include <cmath>
// #include <sstream>
#include "temp/type.h"
#include "temp/temp_assert.h"
#include "temp/math/vector.h"
#include "temp/math/matrix.h"

namespace temp {
namespace math {

template < typename T >
class QuaternionBase;
template < typename T >
QuaternionBase<T> operator*(const QuaternionBase<T> &lhs, const QuaternionBase<T> &rhs);
template < typename T >
QuaternionBase<T> operator*(Float32 lhs, const QuaternionBase<T> &rhs);
template < typename T >
QuaternionBase<T> operator*(const QuaternionBase<T> &lhs, Float32 rhs);
template < typename T >
QuaternionBase<T> operator/(const QuaternionBase<T> &lhs, Float32 rhs);

template<typename T>
class QuaternionBase
{
public:
    QuaternionBase();
    QuaternionBase(T x, T y, T z, T w);
    QuaternionBase(const Vector3Base<T> &euler);

    QuaternionBase(const QuaternionBase &) = default;
    QuaternionBase &operator=(const QuaternionBase &) = default;

#if _MSC_VER<1900
#else
    QuaternionBase(QuaternionBase &&) noexcept = default;
    QuaternionBase &operator=(QuaternionBase &&) noexcept = default;
#endif

    ~QuaternionBase() = default;

    String toString();

    T &x();
    const T &x() const;
    T &y();
    const T &y() const;
    T &z();
    const T &z() const;
    T &w();
    const T &w() const;

    T &operator[](Size index);
    const T &operator[](Size index) const;

    QuaternionBase conjugate() const;

    T absoluteSquared() const;

    T absolute() const;

    QuaternionBase inverse() const;

    Float32 dot() const;

    QuaternionBase normalized() const;

    Matrix44Base<T> toRotateMatrix() const;

    Vector3Base<T> toEulerAnglesZXY() const;

    Vector3Base<T> rotateVector3(const Vector3Base<T> &rhs) const;

    Bool operator==(const QuaternionBase &rhs) const;
    Bool operator!=(const QuaternionBase &rhs) const;

    friend QuaternionBase operator*<T>(const QuaternionBase &lhs, const QuaternionBase &rhs);
    friend QuaternionBase operator*<T>(Float32 lhs, const QuaternionBase &rhs);
    friend QuaternionBase operator*<T>(const QuaternionBase &lhs, Float32 rhs);
    friend QuaternionBase operator/<T>(const QuaternionBase &lhs, Float32 rhs);

private:
	Vector4Base<T> vec4_;

public:
    static const QuaternionBase kZero;
    static const QuaternionBase kIdentity;
};

using Quaternion = QuaternionBase<Float32>;

}   // math
}   // temp

#include "temp/math/quaternion_detail.h"

#endif // GUARD_310e3077c88749ee91ab93a6d1303417
