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
#include "temp/type.h"
#include "temp/temp_assert.h"

namespace temp {
namespace math {

/**
 * @brief
 *
 * @tparam T
 */
template < typename T >
class Vector2Base {
public:

    Vector2Base() : Vector2Base((T)0, (T)0) {}

    Vector2Base(T x, T y) {
        elements_[0] = x;
        elements_[1] = y;
    }

    String ToString() const {
        std::stringstream ss;
        ss << "Vector2( " << x() << ", " << y() << " )";
        return ss.str();
    }

    T &x() { return elements_[0]; }
    const T &x() const { return elements_[0]; }
    T &y() { return elements_[1]; }
    const T &y() const { return elements_[1]; }

    T &operator[](Size index) { TEMP_ASSERT(index <= 1, ""); return elements_[index]; }
    const T &operator[](Size index) const { TEMP_ASSERT(index <= 1, ""); return elements_[index]; }

    Float32 lengthSquared() const { return (elements_[0] * elements_[0]) + (elements_[1] * elements_[1]); }
    Float32 length() const { return std::sqrt(lengthSquared()); }
    Float32 normalized() const { return (*this) / length(); }

    bool operator==(const Vector2Base &rhs) {
        return (elements_[0] == rhs.elements_[0]) && (elements_[1] == rhs.elements_[1]);
    }

    bool operator!=(const Vector2Base &rhs) {
        return !(*this == rhs);
    }

    Vector2Base operator-() const {
        return Vector2Base(-elements_[0], -elements_[1]);
    }

    Vector2Base operator+(const Vector2Base &rhs) {
        return Vector2Base(elements_[0] + rhs.elements_[0], elements_[1] + rhs.elements_[1]);
    }

    Vector2Base operator-(const Vector2Base &rhs) {
        return Vector2Base(elements_[0] - rhs.elements_[0], elements_[1] - rhs.elements_[1]);
    }

    friend Vector2Base operator*(Float32 lhs, const Vector2Base &rhs) {
        return Vector2Base(lhs * rhs.elements_[0], lhs * rhs.elements_[1]);
    }

    friend Vector2Base operator*(const Vector2Base &lhs, Float32 rhs) {
        return rhs * lhs;
    }

    friend Vector2Base operator/(const Vector2Base &lhs, Float32 rhs) {
        return Vector2Base(lhs.elements_[0]/rhs, lhs.elements_[1]/rhs);
    }

    static T dot(const Vector2Base &lhs, const Vector2Base &rhs) {
        return lhs.elements_[0] * rhs.elements_[0] + lhs.elements_[1] * rhs.elements_[1];
    }

public:
    static const Vector2Base kZero;
    static const Vector2Base kLeft;
    static const Vector2Base kRight;
    static const Vector2Base kUp;
    static const Vector2Base kDown;

private:
    T elements_[2];
};

template < typename T >
const Vector2Base< T > Vector2Base< T >::kZero = Vector2Base< T >();
template < typename T >
const Vector2Base< T > Vector2Base< T >::kLeft = Vector2Base< T >((T)-1, (T)0);
template < typename T >
const Vector2Base< T > Vector2Base< T >::kRight = Vector2Base< T >((T)1, (T)0);
template < typename T >
const Vector2Base< T > Vector2Base< T >::kUp = Vector2Base< T >((T)0, (T)1);
template < typename T >
const Vector2Base< T > Vector2Base< T >::kDown = Vector2Base< T >((T)0, (T)-1);



using Vector2 = Vector2Base< Float32 >;
using Vector2F64 = Vector2Base< Float64 >;

template < typename T >
class Vector3Base {
public:
    Vector3Base(T x, T y, T z) {
        elements_[0] = x;
        elements_[1] = y;
        elements_[2] = z;
    }

    Vector3Base() : Vector3Base((T)0, (T)0, (T)0) {}

    String ToString() const {
        std::stringstream ss;
        ss << "Vector3( " << x() << ", " << y() << ", " << z() << " )";
        return ss.str();
    }

    T &x() { return elements_[0]; }
    const T &x() const { return elements_[0]; }
    T &y() { return elements_[1]; }
    const T &y() const { return elements_[1]; }
    T &z() { return elements_[2]; }
    const T &z() const { return elements_[2]; }
    
    T &operator[](Size index) { TEMP_ASSERT(index <= 2, ""); return elements_[index]; }
    const T &operator[](Size index) const { TEMP_ASSERT(index <= 2, ""); return elements_[index]; }

    Float32 lengthSquared() const { return (elements_[0] * elements_[0]) + (elements_[1] * elements_[1]); }
    Float32 length() const { return std::sqrt(lengthSquared()); }
    Float32 normalized() const { return (*this) / length(); }

    bool operator==(const Vector3Base &rhs) {
        return (elements_[0] == rhs.elements_[0]) && (elements_[1] == rhs.elements_[1]) && (elements_[2] == rhs.elements_[2]);
    }

    bool operator!=(const Vector3Base &rhs) {
        return !(*this == rhs);
    }

    Vector3Base operator-() {
        return Vector3Base(-elements_[0], -elements_[1], -elements_[2]);
    }

    Vector3Base operator+(const Vector3Base &rhs) {
        return Vector3Base(elements_[0] + rhs.elements_[0], elements_[1] + rhs.elements_[1], elements_[2] + rhs.elements_[2]);
    }

    Vector3Base operator-(const Vector3Base &rhs) {
        return Vector3Base(elements_[0] - rhs.elements_[0], elements_[1] - rhs.elements_[1], elements_[2] + rhs.elements_[2]);
    }

    friend Vector3Base operator*(Float32 lhs, const Vector3Base &rhs) {
        return Vector3Base(lhs * rhs.elements_[0], lhs * rhs.elements_[1], lhs * rhs.elements_[2]);
    }

    friend Vector3Base operator*(const Vector3Base &lhs, Float32 rhs) {
        return rhs * lhs;
    }

    friend Vector3Base operator/(const Vector3Base &lhs, Float32 rhs) {
        return Vector3Base(lhs.elements_[0]/rhs, lhs.elements_[1]/rhs, lhs.elements_[2]/rhs);
    }

    static Float32 angle(const Vector3Base &lhs, const Vector3Base &rhs) {
        return acos(dot(lhs, rhs)/sqrt(lhs.lengthSquared * rhs.lengthSquared));
    }

    static T dot(const Vector3Base &lhs, const Vector3Base &rhs) {
        return lhs.elements_[0] * rhs.elements_[0] + lhs.elements_[1] * rhs.elements_[1] + lhs.elements_[2] * rhs.elements_[2];
    }

private:
    T elements_[3];

public:
    static const Vector3Base kZero;
    static const Vector3Base kBasisX;
    static const Vector3Base kBasisY;
    static const Vector3Base kBasisZ;
};

using Vector3 = Vector3Base< Float32 >;


template < typename T >
class Vector4 {
public:
    Vector4(T x, T y, T z, T w)
        : x_(x)
        , y_(y)
        , z_(z)
        , w_(w) {}

    Vector4() : Vector4((T)0, (T)0, (T)0, (T)0) {}

    T &x() { return x_; }
    const T &x() const { return x_; }
    T &y() { return y_; }
    const T &y() const { return y_; }
    T &z() { return z_; }
    const T &z() const { return z_; }
    T &w() { return w_; }
    const T &w() const { return w_; }

private:
    T x_;
    T y_;
    T z_;
    T w_;

public:
    static const Vector4 kZero;
    static const Vector4 kBasisX;
    static const Vector4 kBasisY;
    static const Vector4 kBasisZ;
    static const Vector4 kBasisW;
};

using Vector4f = Vector4< Float32 >;

} // namespace math
} // namespace temp

#endif // GUARD_f38e9a44859545f0be2822de4f33f79a
