/**
 * @file render_common.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-20
 */
#pragma once
#ifndef GUARD_617c32ac490746cfba0ca3f38a014ecf
#define GUARD_617c32ac490746cfba0ca3f38a014ecf

#include "temp/container.h"
#include "temp/define.h"
#include "temp/temp_assert.h"
#include "temp/temp_math.h"
#include "temp/type.h"

namespace temp {
namespace render {

struct DrawAreaSize {
    Size width;
    Size height;
};

enum class ViewType {
    kShadow,
    kEnvironment,
    kMain,
};

enum class ProjectionType {
    kPerspective,
    kOrthographic,
};

struct PerspectiveParam {
    Float32 near_clip;
    Float32 far_clip;
    Float32 fov;
    Float32 aspect;

    PerspectiveParam()
        : near_clip(0.5f)
        , far_clip(1000.0f)
        , fov(temp::math::pi() / 6.0f)
        , aspect(16.0f / 9.0f) {}
};

struct OrthographicParam {
    Float32 near_clip;
    Float32 far_clip;
    Float32 width;
    Float32 height;

    OrthographicParam()
        : near_clip(0.5f), far_clip(1000.0f), width(30.0f), height(30.0f) {}
};
}
}

#endif  // GUARD_617c32ac490746cfba0ca3f38a014ecf
