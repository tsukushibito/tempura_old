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

namespace temp {
namespace math {

class Quaternion
{
public:
    Quaternion() : Quaternion(0.0f, 0.0f, 0.0f, 0.0f) { }
    Quaternion(Float32 x, Float32 y, Float32 z, Float32 w) {
        elements_[0] = x;
        elements_[1] = y;
        elements_[2] = z;
        elements_[3] = w;
    }

    Quaternion(const Quaternion &) = default;
    Quaternion &operator=(const Quaternion &) = default;

    Quaternion(Quaternion &&) = default;
    Quaternion &operator=(Quaternion &&) = default;

    ~Quaternion() = default;

    String ToString() {
        std::stringstream ss;
        ss << "Quaternion( " << x() << ", " << y() << ", " << z() << ", " << w() << " )";
        return ss.str();
    }

    Float32 &x() { return elements_[0]; }
    const Float32 &x() const { return elements_[0]; }
    Float32 &y() { return elements_[1]; }
    const Float32 &y() const { return elements_[1]; }
    Float32 &z() { return elements_[2]; }
    const Float32 &z() const { return elements_[2]; }
    Float32 &w() { return elements_[3]; }
    const Float32 &w() const { return elements_[3]; }

    Float32 &operator[](Size index) { TEMP_ASSERT(index <= 3, ""); return elements_[index]; }
    const Float32 &operator[](Size index) const { TEMP_ASSERT(index <= 3, ""); return elements_[index]; }

    Quaternion conjugate() const {
        return Quaternion(-x(), -y(), -z(), w());
    }

    Float32 absoluteSquared() const {
        return (x() * x()) + (y() * y()) + (z() * z()) + (w() * w());
    }

    Float32 absolute() const {
        return sqrt(absoluteSquared());
    }

    Quaternion inverse() const {
        return conjugate() / absoluteSquared();
    }

    friend Quaternion operator+(const Quaternion &lhs, const Quaternion &rhs) {
        return Quaternion(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z(), lhs.w() + rhs.w());
    }

    friend Quaternion operator*(const Quaternion &lhs, const Quaternion &rhs) {
        return Quaternion(
            lhs.w() * rhs.x() + lhs.x() * rhs.w() + lhs.y() * rhs.z() - lhs.z() * rhs.y(),
            lhs.w() * rhs.y() - lhs.x() * rhs.z() + lhs.y() * rhs.w() + lhs.z() * rhs.x(),
            lhs.w() * rhs.z() + lhs.x() * rhs.y() - lhs.y() * rhs.x() + lhs.z() * rhs.w(),
            lhs.w() * rhs.w() - lhs.x() * rhs.x() - lhs.y() * rhs.y() - lhs.z() * rhs.z(),
            );
    }

    friend Quaternion operator*(Float32 lhs, const Quaternion &rhs) {
        return Quaternion(lhs * x(), lhs * y(), lhs * z(), lhs * w());
    }

    friend Quaternion operator*(const Quaternion &lhs, Float32 rhs) {
        return rhs * lhs;
    }

    friend Quaternion operator/(const Quaternion &lhs, Float32 rhs) {
        return lhs * (1 / rhs);
    }

private:
    Float32 elements_[4];

public:
    static const Quaternion kZero;
    static const Quaternion kIdentity;
};

}   // math
}   // temp

#endif // GUARD_310e3077c88749ee91ab93a6d1303417
