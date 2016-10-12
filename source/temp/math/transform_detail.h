/**
 * @file transform_detail.h
 * @brief transform detail
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-10-07
 */
#pragma once
#ifndef GUARD_8b90b9dcb3924f1db0765c6aef6a3203
#define GUARD_8b90b9dcb3924f1db0765c6aef6a3203

#include "temp/math/transform_detail.h"

namespace temp {
namespace math {

template<typename T>
TransformBase<T>::TransformBase() 
	: TransformBase(Vec3::kZero, Quat::kIdentity, Vec3(1, 1, 1)) {
}

template<typename T>
TransformBase<T>::TransformBase(const Vec3 &pos, const Quat &rot, const Vec3 &scale) 
	: position_(pos), rotation_(rot), scale_(scale) {
}

template<typename T>
String TransformBase<T>::toString() const {
    std::stringstream ss;
	ss << "Transform( " << std::endl;
	ss << "    position: " << position_.x() << ", " << position_.y() << ", " << position_.z() << std::endl;
	auto rot = rotation_.toEulerAnglesZXY();
	ss << "    rotation: " << rot.x() << ", " << rot.y() << ", " << rot.z() << std::endl;
	ss << "    scale: " << scale_.x() << ", " << scale_.y() << ", " << scale_.z() << std::endl;
	ss << ")" << std::endl;
    return ss.str();
}

template<typename T>
typename TransformBase<T>::Mat44 TransformBase<T>::toMatrix() const {
	using Vec4 = Vector4Base<T>;
	Mat44 rot = rotation_.toRotateMatrix();
	Mat44 scale(ColOrder(), 
		Vec4(scale_.x(), 0, 0, 0), 
		Vec4(0, scale_.y(), 0, 0), 
		Vec4(0, 0, scale_.z(), 0), 
		Vec4(0, 0, 0, 1));
	Mat44 output = scale * rot;
	output[0][3] = position_.x();
	output[1][3] = position_.y();
	output[2][3] = position_.z();
	return output;
}

template<typename T>
TransformBase<T> TransformBase<T>::operator*(const TransformBase<T> &rhs) const {
	return combine(rhs);
}

template<typename T>
TransformBase<T> TransformBase<T>::combine(const TransformBase<T> &rhs) const {
	return TransformBase<T>(Vec3(position_) + rhs.position_, rotation_ * rhs.rotation_, scale_ * rhs.scale_);
}

template<typename T>
const typename TransformBase<T>::Vec3 &TransformBase<T>::position() const {
	return position_;
}

template<typename T>
const typename TransformBase<T>::Quat &TransformBase<T>::rotation() const {
	return rotation_;
}

template<typename T>
const typename TransformBase<T>::Vec3 &TransformBase<T>::scale() const {
	return scale_;
}

}
}
#endif // GUARD_8b90b9dcb3924f1db0765c6aef6a3203
