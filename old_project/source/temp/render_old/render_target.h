/**
 * @file render_target.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-08-20
 */
#pragma once
#ifndef GUARD_38003be94fc74fd39410fa74fb012e1e
#define GUARD_38003be94fc74fd39410fa74fb012e1e

#include "temp/container.h"
#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics/graphics.h"

namespace temp {
namespace render_old {

class RenderTarget : public SmartPointerObject<RenderTarget> {
    friend class Renderer;

public:
    using TextureSPtr = temp::graphics::Texture::SPtr;

private:
    RenderTarget() = default;
    explicit RenderTarget(const RenderTargetDesc& desc);

public:
    ~RenderTarget();


    TextureSPtr texture() const { return texture_; }

private:
    TextureSPtr texture_;
};
}
}

#endif  // GUARD_38003be94fc74fd39410fa74fb012e1e
