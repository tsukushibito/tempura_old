/**
 * @file renderer.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-08-15
 */
#pragma once
#ifndef GUARD_4b7e6e19086d4f838e50af8e09862223
#define GUARD_4b7e6e19086d4f838e50af8e09862223

#include "temp/container.h"
#include "temp/define.h"
#include "temp/type.h"

#include "temp/system/file_system.h"
#include "temp/system/thread_pool.h"

#include "temp/graphics/device.h"

#include "temp/render/camera.h"
#include "temp/render/render_common.h"

namespace temp {
namespace render {

class Renderer : public SmartPointerObject<Renderer> {
    friend class SmartPointerObject<Renderer>;

public:
    using Path               = temp::system::Path;
    using ThreadPoolSPtr     = temp::system::ThreadPool::SPtr;
    using GraphicsDeviceSPtr = temp::graphics::DeviceSPtr;
    using RenderTargetSPtr   = temp::graphics::RenderTargetSPtr;
    using RenderTargetDesc   = temp::graphics::RenderTargetDesc;

private:
    Renderer(const ThreadPoolSPtr&     command_thread,
             const ThreadPoolSPtr&     render_thread,
             const GraphicsDeviceSPtr& device,
             const DrawAreaSize& draw_area_size, const Path& shader_directory);

public:
    ~Renderer();

    RenderTargetSPtr createRenderTarget(const RenderTargetDesc& desc);

    Camera::SPtr createCamera();

    void setMainCamera(const Camera::SPtr& camera);

    void render();

private:
    ThreadPoolSPtr     command_thread_;
    ThreadPoolSPtr     render_thread_;
    GraphicsDeviceSPtr graphics_device_;

    DrawAreaSize draw_area_size_;

    Path shader_directory_;

    std::mutex            camera_list_mutex_;
    temp::Vector<Camera*> camera_list_;
    Camera::WPtr          main_camera_;

    class Impl;
    using ImplUPtr = std::unique_ptr<Impl>;
    ImplUPtr impl_;
};
}
}

#endif  // GUARD_4b7e6e19086d4f838e50af8e09862223
