/**
 * @file camera.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-29
 */
#pragma once
#ifndef GUARD_102f3f8e572543cc9cef288c8bc5ee8d
#define GUARD_102f3f8e572543cc9cef288c8bc5ee8d

#include "temp/graphics/device.h"
#include "temp/render/render_common.h"

namespace temp {
namespace render {

class Camera : public SmartPointerObject<Camera> {
    friend class Renderer;

private:
    Camera() = default;

public:
    ~Camera() {}

    ViewType& viewType() { return view_type_; }

    ProjectionType& projectionType() { return projection_type_; }

    const graphics::RenderTargetSPtr& renderTarget() const { return render_target_; }

    graphics::Viewport& viewport() { return viewport_; }

    Color& clearColor() { return clearColor_; }

    PerspectiveParam& perspectiveParam() { return perspective_param_; }

    OrthographicParam& orthographicParam() { return orthographic_param_; }

private:
    ViewType           view_type_       = ViewType::kMain;
    ProjectionType     projection_type_ = ProjectionType::kPerspective;
    graphics::RenderTarget::SPtr render_target_;
    graphics::Viewport           viewport_;
    Color              clearColor_;
    PerspectiveParam   perspective_param_;
    OrthographicParam  orthographic_param_;
};
}
}

#endif  // GUARD_102f3f8e572543cc9cef288c8bc5ee8d
