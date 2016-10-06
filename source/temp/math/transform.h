/**
 * @file transform.h
 * @brief transform
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-09-25
 */
#pragma once
#ifndef GUARD_eda5a08059f94525963f08502bb89b8a
#define GUARD_eda5a08059f94525963f08502bb89b8a

#include "temp/math/vector.h"
#include "temp/math/matrix.h"
#include "temp/math/quaternion.h"

namespace temp {
namespace math {

template<typename T>
class TransformBase {
public:
    TransformBase() : TransformBase(Vec3::kZero, Quat::kIdentity, Vec3(1, 1, 1)) {}
private:
    using Vec3 = Vector3Base<T>;
    using Quat = QuaternionBase<T>;

    Vec3 translation_;
    Quat rotation_;
    Vec3 scale_;
};
    
} // namespace math
} // namespace temp

#endif // GUARD_eda5a08059f94525963f08502bb89b8a
