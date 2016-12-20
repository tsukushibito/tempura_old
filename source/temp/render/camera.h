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

#include "temp/type.h"
#include "temp/container.h"
#include "temp/math/matrix.h"

namespace temp {
namespace render {

class Renderer;
class RenderTarget;
using RenderTargetSPtr = std::shared_ptr<RenderTarget>;

class Camera : public SmartPointerObject< Camera > {
    friend Renderer;
private:
    static SPtr create();

    Camera();

public:
    ~Camera();

private:
    
    temp::math::Matrix44SPtr worldMatrix_;
    Float32 fov_;
};

} // namespace render
} // namespace temp

#endif // GUARD_082c71951f804213bb68ce9b2d068884
