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
#include "type.h"

namespace temp {
namespace math {

/**
 * @brief
 *
 * @tparam T
 */
template < typename T >
class Vector2 {
public:

    Vector2() : Vector2((T)0, (T)0) {}

    Vector2(T x, T y)
        : x_(x)
        , y_(y) {}


    T &x() { return x_; }
    const T &x() const { return x_; }
    T &y() { return y_; }
    const T &y() const { return y_; }

    Float32 lengthSquared() const { return (x_ * x_) + (y_ * y_); }
    Float32 length() const { return std::sqrt(lengthSquared()); }
    Float32 normalized() const { return (*this) / length(); }

private:
    T x_;
    T y_;

public:
    static const Vector2 kZero;
    static const Vector2 kBasisX;
    static const Vector2 kBasisY;
};

template < typename T >
const Vector2< T > Vector2< T >::kZero = Vector2< T >();
template < typename T >
const Vector2< T > Vector2< T >::kBasisX = Vector2< T >((T)1, (T)0);
template < typename T >
const Vector2< T > Vector2< T >::kBasisY = Vector2< T >((T)0, (T)1);

template < typename T >
bool operator==(const Vector2< T > &lhs, const Vector2< T > &rhs) {
    return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y());
}

template < typename T >
bool operator!=(const Vector2< T > &lhs, const Vector2< T > &rhs) {
    return !(lhs == rhs);
}

template < typename T >
Vector2< T > operator-(const Vector2< T > vec) {
    return Vector2< T >(-vec.x(), -vec.y());
}

template < typename T >
Vector2< T > operator+(const Vector2< T > &lhs, const Vector2< T > &rhs) {
    return Vector2< T >(lhs.x() + rhs.x(), lhs.y() + rhs.y());
}

template < typename T >
Vector2< T > operator-(const Vector2< T > &lhs, const Vector2< T > &rhs) {
    return Vector2< T >(lhs.x() - rhs.x(), lhs.y() - rhs.y());
}

template < typename T >
Vector2< T > operator*(Float32 lhs, const Vector2< T > &rhs) {
    return Vector2< T >(lhs * rhs.x(), lhs * rhs.y());
}

template < typename T >
Vector2< T > operator*(const Vector2< T > lhs, Float32 rhs) {
    return rhs * lhs;
}

template < typename T >
Vector2< T > operator/(Float32 lhs, const Vector2< T > &rhs) {
    return Vector2< T >(lhs / rhs.x(), lhs / rhs.y());
}

template < typename T >
Vector2< T > operator/(const Vector2< T > lhs, Float32 rhs) {
    return rhs / lhs;
}

template < typename T >
T dot(const Vector2< T > &lhs, const Vector2< T > &rhs) {
    return lhs.x() * rhs.x() + lhs.y() * rhs.y();
}

using Vector2F32 = Vector2< Float32 >;
using Vector2F64 = Vector2< Float64 >;

template < typename T >
class Vector3 {
public:
    Vector3(T x, T y, T z)
        : x_(x)
        , y_(y)
        , z_(z) {}

    Vector3() : Vector3((T)0, (T)0, (T)0) {}

    T &x() { return x_; }
    const T &x() const { return x_; }
    T &y() { return y_; }
    const T &y() const { return y_; }
    T &z() { return z_; }
    const T &z() const { return z_; }

private:
    T x_;
    T y_;
    T z_;

public:
    static const Vector3 kZero;
    static const Vector3 kBasisX;
    static const Vector3 kBasisY;
    static const Vector3 kBasisZ;
};

using Vector3f = Vector3< Float32 >;

template < typename T >
Vector3< T > operator+(const Vector3< T > &lhs, const Vector3< T > &rhs) {
    return Vector3< T >(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

template < typename T >
Vector3< T > operator-(const Vector3< T > &lhs, const Vector3< T > &rhs) {
    return Vector3< T >(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z());
}

template < typename T >
T dot(const Vector3< T > &lhs, const Vector3< T > &rhs) {
    return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() + rhs.z();
}

template < typename T >
Vector3< T > cross(const Vector3< T > &lhs, const Vector3< T > &rhs) {
    return Vector3< T >(lhs.y() * rhs.z() - lhs.z() * rhs.y(), lhs.z() * rhs.x() - lhs.x() * rhs.z(),
                        lhs.x() * rhs.y() - lhs.y() * rhs.x());
}

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
