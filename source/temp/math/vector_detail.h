/**
 * @file vector_detail.h
 * @brief vector detail
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-09-05
 */
#pragma once
#ifndef GUARD_923a45137e644732b2ad7b231432483b
#define GUARD_923a45137e644732b2ad7b231432483b

#include "temp/math/vector.h"

namespace temp {
namespace math {

template <typename T>
Vector2Base<T>::Vector2Base() : Vector2Base((T)0, (T)0) {}

template <typename T>
Vector2Base<T>::Vector2Base(T x, T y) {
    elements_[0] = x;
    elements_[1] = y;
}

template <typename T>
String Vector2Base<T>::toString() const {
    std::stringstream ss;
    ss << "Vector2( " << x() << ", " << y() << " )";
    return ss.str();
}

template <typename T>
T& Vector2Base<T>::x() {
    return elements_[0];
}

template <typename T>
const T& Vector2Base<T>::x() const {
    return elements_[0];
}

template <typename T>
T& Vector2Base<T>::y() {
    return elements_[1];
}

template <typename T>
const T& Vector2Base<T>::y() const {
    return elements_[1];
}

template <typename T>
T& Vector2Base<T>::operator[](Size index) {
    TEMP_ASSERT(index <= 1, "");
    return elements_[index];
}

template <typename T>
const T& Vector2Base<T>::operator[](Size index) const {
    TEMP_ASSERT(index <= 1, "");
    return elements_[index];
}

template <typename T>
Float32 Vector2Base<T>::lengthSquared() const {
    return (elements_[0] * elements_[0]) + (elements_[1] * elements_[1]);
}

template <typename T>
Float32 Vector2Base<T>::length() const {
    return std::sqrt(lengthSquared());
}

template <typename T>
Float32 Vector2Base<T>::normalized() const {
    return (*this) / length();
}

template <typename T>
bool Vector2Base<T>::operator==(const Vector2Base& rhs) {
    return (elements_[0] == rhs.elements_[0])
           && (elements_[1] == rhs.elements_[1]);
}

template <typename T>
bool Vector2Base<T>::operator!=(const Vector2Base& rhs) {
    return !(*this == rhs);
}

template <typename T>
Vector2Base<T> Vector2Base<T>::operator-() const {
    return Vector2Base(-elements_[0], -elements_[1]);
}

template <typename T>
Vector2Base<T> Vector2Base<T>::operator+(const Vector2Base& rhs) {
    return Vector2Base(elements_[0] + rhs.elements_[0],
                       elements_[1] + rhs.elements_[1]);
}

template <typename T>
Vector2Base<T> Vector2Base<T>::operator-(const Vector2Base& rhs) {
    return Vector2Base(elements_[0] - rhs.elements_[0],
                       elements_[1] - rhs.elements_[1]);
}

template <typename T>
Vector2Base<T> operator*(Float32 lhs, const Vector2Base<T>& rhs) {
    return Vector2Base<T>(lhs * rhs.elements_[0], lhs * rhs.elements_[1]);
}

template <typename T>
Vector2Base<T> operator*(const Vector2Base<T>& lhs, Float32 rhs) {
    return rhs * lhs;
}

template <typename T>
Vector2Base<T> operator/(const Vector2Base<T>& lhs, Float32 rhs) {
    return Vector2Base<T>(lhs.elements_[0] / rhs, lhs.elements_[1] / rhs);
}

template <typename T>
T Vector2Base<T>::dot(const Vector2Base<T>& lhs, const Vector2Base<T>& rhs) {
    return lhs.elements_[0] * rhs.elements_[0]
           + lhs.elements_[1] * rhs.elements_[1];
}

template <typename T>
const Vector2Base<T> Vector2Base<T>::kZero = Vector2Base<T>();
template <typename T>
const Vector2Base<T> Vector2Base<T>::kLeft = Vector2Base<T>((T)-1, (T)0);
template <typename T>
const Vector2Base<T> Vector2Base<T>::kRight = Vector2Base<T>((T)1, (T)0);
template <typename T>
const Vector2Base<T> Vector2Base<T>::kUp = Vector2Base<T>((T)0, (T)1);
template <typename T>
const Vector2Base<T> Vector2Base<T>::kDown = Vector2Base<T>((T)0, (T)-1);

template <typename T>
Vector3Base<T>::Vector3Base() : Vector3Base((T)0, (T)0, (T)0) {}

template <typename T>
Vector3Base<T>::Vector3Base(T x, T y, T z) {
    elements_[0] = x;
    elements_[1] = y;
    elements_[2] = z;
}

template <typename T>
String Vector3Base<T>::toString() const {
    std::stringstream ss;
    ss << "Vector3( " << x() << ", " << y() << ", " << z() << " )";
    return ss.str();
}

template <typename T>
T& Vector3Base<T>::x() {
    return elements_[0];
}

template <typename T>
const T& Vector3Base<T>::x() const {
    return elements_[0];
}

template <typename T>
T& Vector3Base<T>::y() {
    return elements_[1];
}

template <typename T>
const T& Vector3Base<T>::y() const {
    return elements_[1];
}

template <typename T>
T& Vector3Base<T>::z() {
    return elements_[2];
}

template <typename T>
const T& Vector3Base<T>::z() const {
    return elements_[2];
}

template <typename T>
T& Vector3Base<T>::operator[](Size index) {
    TEMP_ASSERT(index <= 2, "");
    return elements_[index];
}

template <typename T>
const T& Vector3Base<T>::operator[](Size index) const {
    TEMP_ASSERT(index <= 2, "");
    return elements_[index];
}

template <typename T>
Vector3Base<T> Vector3Base<T>::xyz() const {
    return *this;
};

template <typename T>
Vector3Base<T> Vector3Base<T>::xzy() const {
    return Vector3Base<T>(x(), z(), y());
};

template <typename T>
Vector3Base<T> Vector3Base<T>::yxz() const {
    return Vector3Base<T>(y(), x(), z());
};

template <typename T>
Vector3Base<T> Vector3Base<T>::yzx() const {
    return Vector3Base<T>(y(), z(), x());
};

template <typename T>
Vector3Base<T> Vector3Base<T>::zxy() const {
    return Vector3Base<T>(z(), x(), y());
};

template <typename T>
Vector3Base<T> Vector3Base<T>::zyx() const {
    return Vector3Base<T>(z(), y(), x());
};

template <typename T>
Float32 Vector3Base<T>::lengthSquared() const {
    return (elements_[0] * elements_[0]) + (elements_[1] * elements_[1]);
}

template <typename T>
Float32 Vector3Base<T>::length() const {
    return std::sqrt(lengthSquared());
}

template <typename T>
Vector3Base<T> Vector3Base<T>::normalized() const {
    return (*this) / length();
}

template <typename T>
Bool Vector3Base<T>::operator==(const Vector3Base<T>& rhs) {
    return (elements_[0] == rhs.elements_[0])
           && (elements_[1] == rhs.elements_[1])
           && (elements_[2] == rhs.elements_[2]);
}

template <typename T>
Bool Vector3Base<T>::operator!=(const Vector3Base<T>& rhs) {
    return !(*this == rhs);
}

template <typename T>
Vector3Base<T> Vector3Base<T>::operator-() {
    return Vector3Base<T>(-elements_[0], -elements_[1], -elements_[2]);
}

template <typename T>
Vector3Base<T> Vector3Base<T>::operator+(const Vector3Base<T>& rhs) {
    return Vector3Base<T>(elements_[0] + rhs.elements_[0],
                          elements_[1] + rhs.elements_[1],
                          elements_[2] + rhs.elements_[2]);
}

template <typename T>
Vector3Base<T> Vector3Base<T>::operator-(const Vector3Base<T>& rhs) {
    return Vector3Base<T>(elements_[0] - rhs.elements_[0],
                          elements_[1] - rhs.elements_[1],
                          elements_[2] + rhs.elements_[2]);
}

template <typename T>
Vector3Base<T> operator*(Float32 lhs, const Vector3Base<T>& rhs) {
    return Vector3Base<T>(lhs * rhs.elements_[0], lhs * rhs.elements_[1],
                          lhs * rhs.elements_[2]);
}

template <typename T>
Vector3Base<T> operator*(const Vector3Base<T>& lhs, Float32 rhs) {
    return rhs * lhs;
}

template <typename T>
Vector3Base<T> operator*(const Vector3Base<T>& lhs, const Vector3Base<T>& rhs) {
    return Vector3Base<T>(lhs.x() * rhs.x(), lhs.y() * rhs.y(),
                          lhs.z() * rhs.z());
}

template <typename T>
Vector3Base<T> operator/(const Vector3Base<T>& lhs, Float32 rhs) {
    return Vector3Base<T>(lhs.elements_[0] / rhs, lhs.elements_[1] / rhs,
                          lhs.elements_[2] / rhs);
}

template <typename T>
Float32 Vector3Base<T>::angle(const Vector3Base<T>& lhs,
                              const Vector3Base<T>& rhs) {
    return acos(dot(lhs, rhs)
                / sqrt(lhs.lengthSquared() * rhs.lengthSquared()));
}

template <typename T>
Vector3Base<T> Vector3Base<T>::cross(const Vector3Base<T>& lhs,
                                     const Vector3Base<T>& rhs) {
    auto a0 = lhs.yzx();
    auto b0 = rhs.zxy();
    auto a1 = lhs.zxy();
    auto b1 = rhs.yzx();
    return a0 * b0 - a1 * b1;
}

template <typename T>
Float32 Vector3Base<T>::distance(const Vector3Base& lhs,
                                 const Vector3Base& rhs) {
    return (lhs - rhs).length();
}

template <typename T>
T Vector3Base<T>::dot(const Vector3Base& lhs, const Vector3Base& rhs) {
    return lhs.elements_[0] * rhs.elements_[0]
           + lhs.elements_[1] * rhs.elements_[1]
           + lhs.elements_[2] * rhs.elements_[2];
}

template <typename T>
const Vector3Base<T> Vector3Base<T>::kZero = Vector3Base<T>();
template <typename T>
const Vector3Base<T> Vector3Base<T>::kLeft = Vector3Base<T>((T)-1, (T)0, (T)0);
template <typename T>
const Vector3Base<T> Vector3Base<T>::kRight = Vector3Base<T>((T)1, (T)0, (T)0);
template <typename T>
const Vector3Base<T> Vector3Base<T>::kUp = Vector3Base<T>((T)0, (T)1, (T)0);
template <typename T>
const Vector3Base<T> Vector3Base<T>::kDown = Vector3Base<T>((T)0, (T)-1, (T)0);
template <typename T>
const Vector3Base<T> Vector3Base<T>::kForward
    = Vector3Base<T>((T)0, (T)0, (T)1);
template <typename T>
const Vector3Base<T> Vector3Base<T>::kBack = Vector3Base<T>((T)0, (T)0, (T)-1);

template <typename T>
Vector4Base<T>::Vector4Base() : Vector4Base((T)0, (T)0, (T)0, (T)0) {}

template <typename T>
Vector4Base<T>::Vector4Base(T x, T y, T z, T w) {
    elements_[0] = x;
    elements_[1] = y;
    elements_[2] = z;
    elements_[3] = w;
}

template <typename T>
String Vector4Base<T>::toString() const {
    std::stringstream ss;
    ss << "Vector4( " << x() << ", " << y() << ", " << z() << ", " << w()
       << " )";
    return ss.str();
}

template <typename T>
T& Vector4Base<T>::x() {
    return elements_[0];
}

template <typename T>
const T& Vector4Base<T>::x() const {
    return elements_[0];
}

template <typename T>
T& Vector4Base<T>::y() {
    return elements_[1];
}

template <typename T>
const T& Vector4Base<T>::y() const {
    return elements_[1];
}

template <typename T>
T& Vector4Base<T>::z() {
    return elements_[2];
}

template <typename T>
const T& Vector4Base<T>::z() const {
    return elements_[2];
}

template <typename T>
T& Vector4Base<T>::w() {
    return elements_[3];
}

template <typename T>
const T& Vector4Base<T>::w() const {
    return elements_[3];
}

template <typename T>
T& Vector4Base<T>::operator[](Size index) {
    TEMP_ASSERT(index <= 3, "");
    return elements_[index];
}

template <typename T>
const T& Vector4Base<T>::operator[](Size index) const {
    TEMP_ASSERT(index <= 3, "");
    return elements_[index];
}

template <typename T>
Bool Vector4Base<T>::operator==(const Vector4Base<T>& rhs) const {
    return (x() == rhs.x()) && (y() == rhs.y()) && (z() == rhs.z())
           && (w() == rhs.w());
}

template <typename T>
Bool Vector4Base<T>::operator!=(const Vector4Base<T>& rhs) const {
    return !((*this) == rhs);
}

template <typename T>
Vector4Base<T> Vector4Base<T>::operator-() {
    return Vector4Base<T>(-x(), -y(), -z(), -w());
}

template <typename T>
Vector4Base<T> Vector4Base<T>::operator+(const Vector4Base<T>& rhs) {
    return Vector4Base<T>(x() + rhs.x(), y() + rhs.y(), z() + rhs.z(),
                          w() + rhs.w());
}

template <typename T>
Vector4Base<T> Vector4Base<T>::operator-(const Vector4Base<T>& rhs) {
    return Vector4Base<T>(x() - rhs.x(), y() - rhs.y(), z() - rhs.z(),
                          w() - rhs.w());
}

template <typename T>
Vector4Base<T> operator*(Float32 lhs, const Vector4Base<T>& rhs) {
    return Vector4Base<T>(lhs * rhs.x(), lhs * rhs.y(), lhs * rhs.z(),
                          lhs * rhs.w());
}

template <typename T>
Vector4Base<T> operator*(const Vector4Base<T>& lhs, Float32 rhs) {
    return rhs * lhs;
}

template <typename T>
Vector4Base<T> operator*(const Vector4Base<T>& lhs, const Vector4Base<T>& rhs) {
    return Vector4Base<T>(lhs.x() * rhs.x(), lhs.y() * rhs.y(),
                          lhs.z() * rhs.z(), lhs.w() * rhs.w());
}

template <typename T>
Vector4Base<T> operator/(const Vector4Base<T>& lhs, Float32 rhs) {
    return lhs * (1 / rhs);
}

template <typename T>
T Vector4Base<T>::dot(const Vector4Base<T>& lhs, const Vector4Base<T>& rhs) {
    return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z()
           + lhs.w() * rhs.w();
}

}  // namespace math
}  // namespace temp

#endif  // GUARD_923a45137e644732b2ad7b231432483b
