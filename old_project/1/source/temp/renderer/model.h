#pragma once
#include "temp/common/common.h"
#include "temp/resource/mesh.h"

namespace temp {
namespace renderer {
struct Model {
  math::Vector3 position;
  math::Quaternion rotation;
  math::Vector3 scale;
};
}  // namespace renderer
}  // namespace temp