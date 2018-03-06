#pragma once
#include "temp/common/common.h"
#include "temp/math/vector3.h"
#include "temp/math/vector4.h"

namespace temp {
namespace math {
class Matrix4x4 {
 public:
 private:
  Vector4 row_[4];
};
}  // namespace math
}  // namespace temp