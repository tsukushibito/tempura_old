/**
 * @file quaternion_detail.h
 * @brief quaternion
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-09-17
 */
#pragma once
#ifndef GUARD_6a33b187b9ef497383f5720a02abac55
#define GUARD_6a33b187b9ef497383f5720a02abac55

namespace temp {
namespace math {

template<typename T>
QuaternionBase<T>::QuaternionBase() : QuaternionBase(0.0f, 0.0f, 0.0f, 0.0f) { }

template<typename T>
QuaternionBase<T>::QuaternionBase(T x, T y, T z, T w) {
    elements_[0] = x;
    elements_[1] = y;
    elements_[2] = z;
    elements_[3] = w;
}

template<typename T>
QuaternionBase<T>::QuaternionBase(const Vector3Base<T> &euler) {
    using std::sin;
    using std::cos;
    auto qx = QuaternionBase<T>(sin(euler.x() / 2), 0, 0, cos(euler.x() / 2));
    auto qy = QuaternionBase<T>(0, sin(euler.y() / 2), 0, cos(euler.y() / 2));
    auto qz = QuaternionBase<T>(0, 0, sin(euler.z() / 2), cos(euler.z() / 2));

    *this = qz * qx * qy;
}

template<typename T>
String QuaternionBase<T>::ToString() {
    std::stringstream ss;
    ss << "QuaternionBase( " << x() << ", " << y() << ", " << z() << ", " << w() << " )";
    return ss.str();
}

template<typename T>
T &QuaternionBase<T>::x() { return elements_[0]; }

template<typename T>
const T &QuaternionBase<T>::x() const { return elements_[0]; }

template<typename T>
T &QuaternionBase<T>::y() { return elements_[1]; }

template<typename T>
const T &QuaternionBase<T>::y() const { return elements_[1]; }

template<typename T>
T &QuaternionBase<T>::z() { return elements_[2]; }

template<typename T>
const T &QuaternionBase<T>::z() const { return elements_[2]; }

template<typename T>
T &QuaternionBase<T>::w() { return elements_[3]; }

template<typename T>
const T &QuaternionBase<T>::w() const { return elements_[3]; }

template<typename T>
T &QuaternionBase<T>::operator[](Size index) { TEMP_ASSERT(index <= 3, ""); return elements_[index]; }

template<typename T>
const T &QuaternionBase<T>::operator[](Size index) const { TEMP_ASSERT(index <= 3, ""); return elements_[index]; }

template<typename T>
QuaternionBase<T> QuaternionBase<T>::conjugate() const {
    return QuaternionBase<T>(-x(), -y(), -z(), w());
}

template<typename T>
T QuaternionBase<T>::absoluteSquared() const {
    return (x() * x()) + (y() * y()) + (z() * z()) + (w() * w());
}

template<typename T>
T QuaternionBase<T>::absolute() const {
    return sqrt(absoluteSquared());
}

template<typename T>
QuaternionBase<T> QuaternionBase<T>::inverse() const {
    return conjugate() / absoluteSquared();
}

template<typename T>
Float32 QuaternionBase<T>::dot() const {
    return vec4_.dot();
}

template<typename T>
QuaternionBase<T> QuaternionBase<T>::normalized() const {
    return (*this) / absolute();
}

template<typename T>
Matrix44Base<T> QuaternionBase<T>::toRotateMatrix() const {
    auto x2 = x() * x();
    auto y2 = y() * y();
    auto z2 = z() * z();
    auto wx = w() * x();
    auto wy = w() * y();
    auto wz = w() * z();
    auto xy = x() * y();
    auto xz = x() * z();
    auto yz = y() * z();

    return Matrix44Base<T>( RowOrder(),
            Vector4Base<T>(1 - 2*y2 - 2*z2, 2*xy + 2*wz,     2*xz - 2*wy,     0),
            Vector4Base<T>(2*xy - 2*wz,     1 - 2*x2 - 2*z2, 2*yz + 2*wx,     0),
            Vector4Base<T>(2*xz - 2*wy,     2*yz - 2*wx,     1 - 2*x2 - 2*y2, 0),
            Vector4Base<T>(0,               0,               0,               1)); 
}

template<typename T>
Bool QuaternionBase<T>::operator==(const QuaternionBase &rhs) const {
    return (x() == rhs.x() && y() == rhs.y() && z() == rhs.z() && w() == rhs.w());
}

template<typename T>
Bool QuaternionBase<T>::operator!=(const QuaternionBase &rhs) const {
    return !(*this == rhs);
}

template<typename T>
QuaternionBase<T> operator*(const QuaternionBase<T> &lhs, const QuaternionBase<T> &rhs) {
    return QuaternionBase<T>(
        lhs.w() * rhs.x() + lhs.x() * rhs.w() + lhs.y() * rhs.z() - lhs.z() * rhs.y(),
        lhs.w() * rhs.y() - lhs.x() * rhs.z() + lhs.y() * rhs.w() + lhs.z() * rhs.x(),
        lhs.w() * rhs.z() + lhs.x() * rhs.y() - lhs.y() * rhs.x() + lhs.z() * rhs.w(),
        lhs.w() * rhs.w() - lhs.x() * rhs.x() - lhs.y() * rhs.y() - lhs.z() * rhs.z(),
        );
}

template<typename T>
QuaternionBase<T> operator*(Float32 lhs, const QuaternionBase<T> &rhs) {
    return QuaternionBase<T>(lhs * x(), lhs * y(), lhs * z(), lhs * w());
}

template<typename T>
QuaternionBase<T> operator*(const QuaternionBase<T> &lhs, Float32 rhs) {
    return rhs * lhs;
}

template<typename T>
QuaternionBase<T> operator/(const QuaternionBase<T> &lhs, Float32 rhs) {
    return lhs * (1 / rhs);
}

template<typename T>
const QuaternionBase<T> QuaternionBase<T>::kZero = QuaternionBase<T>();

template<typename T>
const QuaternionBase<T> QuaternionBase<T>::kIdentity = QuaternionBase<T>((T)0, (T)0, (T)0, (T)1);

}
}

#endif // GUARD_6a33b187b9ef497383f5720a02abac55
