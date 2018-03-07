#pragma once
#include "temp/common/common.h"
#include "temp/math/math.h"

namespace temp {
namespace renderer {
class Camera : public SmartPointerObject<Camera> {
 public:
 private:
  math::Vector3 position_;
  math::Quaternion rotation_;
};
}  // namespace renderer
}  // namespace temp