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

template < typename T >
class TransformBase {
public:
    using Vec3 = Vector3Base< T >;
    using Quat = QuaternionBase< T >;
    using Mat44 = Matrix44Base< T >;

    TransformBase();
    TransformBase(const Vec3 &pos, const Quat &rot, const Vec3 &scale);

    TransformBase(const TransformBase &) = default;
    TransformBase &operator=(const TransformBase &) = default;

#if _MSC_VER<1900
#else
    TransformBase(TransformBase &&) noexcept = default;
    TransformBase &operator=(TransformBase &&) noexcept = default;
#endif

    ~TransformBase() = default;

    String toString() const;

    Mat44 toMatrix() const;

    TransformBase operator*(const TransformBase &rhs) const;
    TransformBase combine(const TransformBase &rhs) const;

    const Vec3 &position() const;
    const Quat &rotation() const;
    const Vec3 &scale() const;

private:
    Vec3 position_;
    Quat rotation_;
    Vec3 scale_;
};

using Transform = TransformBase<Float32>;

} // namespace math
} // namespace temp

#include "temp/math/transform_detail.h"

#endif // GUARD_eda5a08059f94525963f08502bb89b8a
