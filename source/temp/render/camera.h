/**
 * @file camera.h
 * @brief Camera class
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-08-23
 */
#pragma once
#ifndef GUARD_082c71951f804213bb68ce9b2d068884
#define GUARD_082c71951f804213bb68ce9b2d068884

#include "temp/container.h"
#include "temp/math/matrix.h"
#include "temp/math/transform.h"
#include "temp/type.h"

namespace temp {
namespace render {

class Renderer;
class RenderTexture;

enum class ClearFlag {
    SolidColor,
    Skybox,
    DepthOnly,
    DontClear,
};

enum class ProjectionType {
    Perspective,
    Orthographic,
};

struct CameraData {
    math::Matrix44 viewMatrix_;
    math::Matrix44 projMatrix_;

    ClearFlag clearFlag_ = ClearFlag::SolidColor;

    Int32 cullingMask_ = 0xffffffff;

    std::shared_ptr<RenderTexture> renderTexture_;
};

using CameraDataHandle = temp::Handle<CameraData>;

class Camera {
    using RendererWPtr = std::weak_ptr<Renderer>;

public:
    Camera(const RendererWPtr& renderer);

    ~Camera();

    void setTransform(const math::Transform& transform);

    void setPerspective(Float32 fovy, Float32 aspect, Float32 znear,
                        Float32 zfar);

    void setOrthographic(Float32 left, Float32 right, Float32 top,
                         Float32 bottom, Float32 znear, Float32 zfar);

    const CameraData& getData() const;

private:
    RendererWPtr renderer_;

    CameraDataHandle dataHandle_ = -1;

    math::Transform transform_;

    Float32 fovy_   = 0.0f;
    Float32 aspect_ = 0.0f;
    Float32 znear_  = 0.0f;
    Float32 zfar_   = 0.0f;
    Float32 left_   = 0.0f;
    Float32 right_  = 0.0f;
    Float32 top_    = 0.0f;
    Float32 bottom_ = 0.0f;
};

void cameraDataGavageCollect();

}  // namespace render
}  // namespace temp

#endif  // GUARD_082c71951f804213bb68ce9b2d068884
