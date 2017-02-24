/**
 * @file vector.h
 * @brief vector math
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-08-25
 */
#pragma once
#ifndef GUARD_f38e9a44859545f0be2822de4f33f79a
#define GUARD_f38e9a44859545f0be2822de4f33f79a

#include <cmath>
// #include <sstream>
#include "temp/temp_assert.h"
#include "temp/type.h"

namespace temp {
namespace math {

/**
 * @brief
 *
 * @tparam T
 */
template <typename T>
class Vector2Base;
template <typename T>
Vector2Base<T> operator*(Float32 lhs, const Vector2Base<T>& rhs);
template <typename T>
Vector2Base<T> operator*(const Vector2Base<T>& lhs, Float32 rhs);
template <typename T>
Vector2Base<T> operator/(const Vector2Base<T>& lhs, Float32 rhs);

template <typename T>
class Vector2Base {
public:
    Vector2Base();
    Vector2Base(T x, T y);

    Vector2Base(const Vector2Base&) = default;
    Vector2Base& operator=(const Vector2Base&) = default;

    Vector2Base(Vector2Base&&) noexcept = default;
    Vector2Base& operator=(Vector2Base&&) noexcept = default;

    ~Vector2Base() = default;

    String toString() const;

    T&       x();
    const T& x() const;
    T&       y();
    const T& y() const;

    T& operator[](Size index);
    const T& operator[](Size index) const;

    Float32 lengthSquared() const;
    Float32 length() const;
    Float32 normalized() const;

    Bool operator==(const Vector2Base& rhs);
    Bool operator!=(const Vector2Base& rhs);
    Vector2Base operator-() const;
    Vector2Base operator+(const Vector2Base& rhs);
    Vector2Base operator-(const Vector2Base& rhs);

    friend Vector2Base operator*<T>(Float32 lhs, const Vector2Base& rhs);
    friend Vector2Base operator*<T>(const Vector2Base& lhs, Float32 rhs);
    friend Vector2Base operator/<T>(const Vector2Base& lhs, Float32 rhs);

    static T dot(const Vector2Base& lhs, const Vector2Base& rhs);

public:
    static const Vector2Base kZero;
    static const Vector2Base kLeft;
    static const Vector2Base kRight;
    static const Vector2Base kUp;
    static const Vector2Base kDown;

private:
    T elements_[2];
};

using Vector2    = Vector2Base<Float32>;
using Vector2F64 = Vector2Base<Float64>;

template <typename T>
class Vector3Base;
template <typename T>
Vector3Base<T> operator*(Float32 lhs, const Vector3Base<T>& rhs);
template <typename T>
Vector3Base<T> operator*(const Vector3Base<T>& lhs, Float32 rhs);
template <typename T>
Vector3Base<T> operator*(const Vector3Base<T>& lhs, const Vector3Base<T>& rhs);
template <typename T>
Vector3Base<T> operator/(const Vector3Base<T>& lhs, Float32 rhs);

template <typename T>
class Vector3Base {
public:
    Vector3Base();

    Vector3Base(T x, T y, T z);

    Vector3Base(const Vector3Base&) = default;
    Vector3Base& operator=(const Vector3Base&) = default;

    Vector3Base(Vector3Base&&) noexcept = default;
    Vector3Base& operator=(Vector3Base&&) noexcept = default;

    ~Vector3Base() = default;

    String toString() const;

    T&       x();
    const T& x() const;
    T&       y();
    const T& y() const;
    T&       z();
    const T& z() const;

    T& operator[](Size index);
    const T& operator[](Size index) const;

    Vector3Base xyz() const;
    Vector3Base xzy() const;
    Vector3Base yxz() const;
    Vector3Base yzx() const;
    Vector3Base zxy() const;
    Vector3Base zyx() const;

    Float32     lengthSquared() const;
    Float32     length() const;
    Vector3Base normalized() const;

    Bool operator==(const Vector3Base& rhs);
    Bool operator!=(const Vector3Base& rhs);

    Vector3Base operator-();
    Vector3Base operator+(const Vector3Base& rhs);
    Vector3Base operator-(const Vector3Base& rhs);

    friend Vector3Base operator*<T>(Float32 lhs, const Vector3Base& rhs);
    friend Vector3Base operator*<T>(const Vector3Base& lhs, Float32 rhs);
    friend Vector3Base operator*<T>(const Vector3Base& lhs,
                                    const Vector3Base& rhs);
    friend Vector3Base operator/<T>(const Vector3Base& lhs, Float32 rhs);

    static Float32 angle(const Vector3Base& lhs, const Vector3Base& rhs);
    static Vector3Base cross(const Vector3Base& lhs, const Vector3Base& rhs);
    static Float32 distance(const Vector3Base& lhs, const Vector3Base& rhs);
    static T dot(const Vector3Base& lhs, const Vector3Base& rhs);

private:
    T elements_[3];

public:
    static const Vector3Base kZero;
    static const Vector3Base kLeft;
    static const Vector3Base kRight;
    static const Vector3Base kUp;
    static const Vector3Base kDown;
    static const Vector3Base kForward;
    static const Vector3Base kBack;
};

using Vector3 = Vector3Base<Float32>;


template <typename T>
class Vector4Base;
template <typename T>
Vector4Base<T> operator*(Float32 lhs, const Vector4Base<T>& rhs);
template <typename T>
Vector4Base<T> operator*(const Vector4Base<T>& lhs, Float32 rhs);
template <typename T>
Vector4Base<T> operator*(const Vector4Base<T>& lhs, const Vector4Base<T>& rhs);
template <typename T>
Vector4Base<T> operator/(const Vector4Base<T>& lhs, Float32 rhs);

template <typename T>
class Vector4Base {
public:
    Vector4Base();

    Vector4Base(T x, T y, T z, T w);

    Vector4Base(const Vector4Base&) = default;
    Vector4Base& operator=(const Vector4Base&) = default;

    Vector4Base(Vector4Base&&) noexcept = default;
    Vector4Base& operator=(Vector4Base&&) noexcept = default;

    ~Vector4Base() = default;

    String toString() const;

    T&       x();
    const T& x() const;
    T&       y();
    const T& y() const;
    T&       z();
    const T& z() const;
    T&       w();
    const T& w() const;

    T& operator[](Size index);
    const T& operator[](Size index) const;

    Bool operator==(const Vector4Base& rhs) const;
    Bool operator!=(const Vector4Base& rhs) const;

    Vector4Base operator-();
    Vector4Base operator+(const Vector4Base& rhs);
    Vector4Base operator-(const Vector4Base& rhs);

    friend Vector4Base operator*<T>(Float32 lhs, const Vector4Base& rhs);
    friend Vector4Base operator*<T>(const Vector4Base& lhs, Float32 rhs);
    friend Vector4Base operator*<T>(const Vector4Base& lhs,
                                    const Vector4Base& rhs);
    friend Vector4Base operator/<T>(const Vector4Base& lhs, Float32 rhs);

    static T dot(const Vector4Base& lhs, const Vector4Base& rhs);

private:
    T elements_[4];
};

using Vector4 = Vector4Base<Float32>;

}  // namespace math
}  // namespace temp

#include "temp/math/vector_detail.h"

#endif  // GUARD_f38e9a44859545f0be2822de4f33f79a
