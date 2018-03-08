#pragma once
#include "temp/common/common.h"
#include "temp/math/math.h"

namespace temp {
namespace renderer {

enum class ProjectionType {
  kPerspective,
  kOrthographic,
};

struct PerspectiveParameter {
  Float32 near_clip;
  Float32 far_clip;
  Float32 fov;
  Float32 aspect;
};

struct OrthographicParameter {
  Float32 near_clip;
  Float32 far_clip;
  Float32 width;
  Float32 height;
};

struct Viewport {
  Float32 top;
  Float32 left;
  Float32 bottom;
  Float32 right;
};

struct Camera {
  math::Vector3 position;
  math::Quaternion rotation;
  Viewport viewport;
  ProjectionType projection_type;
  PerspectiveParameter perspective_parameter;
  OrthographicParameter orthographic_parameter;
};
}  // namespace renderer
}  // namespace temp