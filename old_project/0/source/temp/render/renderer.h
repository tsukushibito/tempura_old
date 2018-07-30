/**
 * @file renderer.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-28
 */
#pragma once
#ifndef GUARD_aff9e143676144dc885d98357b6a7bba
#define GUARD_aff9e143676144dc885d98357b6a7bba

#include "temp/system/thread_pool.h"

#include "temp/graphics/device.h"

#include "temp/render/camera.h"
#include "temp/render/render_common.h"

namespace temp {
namespace render {

class Renderer : Uncopyable {
public:
    using SPtr = std::shared_ptr<Renderer>;

    virtual ~Renderer() = 0;

    virtual void render() = 0;

    virtual Camera::SPtr createCamera() = 0;

    virtual void setMainCamera(const Camera::SPtr& camera) = 0;
};

Renderer::SPtr createRenderer(const graphics::Device::SPtr&   device,
                              const system::ThreadPool::SPtr& render_thread,
                              const system::ThreadPool::SPtr& worker_thread);
}
}

#endif  // GUARD_aff9e143676144dc885d98357b6a7bba
