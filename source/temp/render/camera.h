/**
 * @file camera.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-08-19
 */
#pragma once
#ifndef GUARD_6bc11c98b40c4c329c12b7a1364ab7d7
#define GUARD_6bc11c98b40c4c329c12b7a1364ab7d7

#include "temp/container.h"
#include "temp/define.h"
#include "temp/type.h"
#include "temp/temp_math.h"

#include "temp/graphics/render_target.h"

namespace temp {
namespace render {

class Renderer;

struct Viewport {
    Float32 top;
    Float32 left;
    Float32 bottom;
    Float32 right;

    Viewport() : top(0.0f), left(0.0f), bottom(1.0f), right(1.0f) {}
};

enum class CameraType {
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

class Camera : public SmartPointerObject<Camera> {
    friend class Renderer;

public:
    using RenderTarget     = temp::graphics::RenderTarget;
    using RenderTargetSPtr = temp::graphics::RenderTargetSPtr;

private:
    Camera(const std::function<void(Camera*)>& on_destroy)
        : on_destroy_(on_destroy) {}

public:
    ~Camera() { on_destroy_(this); }

    RenderTargetSPtr&  renderTarget() { return render_target_; }
    Viewport&          viewport() { return viewport_; }
    Color&             clearColor() { return clearColor_; }
    PerspectiveParam&  perspectiveParam() { return perspective_param_; }
    OrthographicParam& orthographicParam() { return orthographic_param_; }

private:
    std::function<void(Camera*)> on_destroy_;

    RenderTargetSPtr  render_target_;
    Viewport          viewport_;
    Color             clearColor_;
    PerspectiveParam  perspective_param_;
    OrthographicParam orthographic_param_;
};
}
}

#endif  // GUARD_6bc11c98b40c4c329c12b7a1364ab7d7
