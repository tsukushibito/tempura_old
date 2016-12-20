/**
 * @file transform.h
 * @brief transform
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-10-14
 */
#pragma once
#ifndef GUARD_67c15763bd014ef181c339ba34e6572b
#define GUARD_67c15763bd014ef181c339ba34e6572b

#include "temp/temp_math.h"

namespace temp {
namespace scene_graph {

class Transform : public SmartPointerObject<Transform> {
public:
private:
	Transform *_parent;
	math::Vector3 localPosition_;
	math::Quaternion localRotation_;
	math::Vector3 localScale_;
};
    
} // namespace scene_graph
} // namespace temp

#endif // GUARD_67c15763bd014ef181c339ba34e6572b
