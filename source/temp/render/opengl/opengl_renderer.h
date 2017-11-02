/**
 * @file opengl_renderer.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-28
 */
#pragma once
#ifndef GUARD_ab57776103ba468a9fbe45fc77a11914
#define GUARD_ab57776103ba468a9fbe45fc77a11914

#include "temp/render/renderer.h"

#include "temp/graphics/opengl/opengl_device.h"

namespace temp {
namespace render {
namespace opengl {

class OpenGLRenderer : public Renderer,
                       public SmartPointerObject<OpenGLRenderer> {
public:
    OpenGLRenderer(const graphics::Device::SPtr&   device,
                   const system::ThreadPool::SPtr& render_thread);

    ~OpenGLRenderer();

    void render() override;

    Camera::SPtr createCamera() override;

    void setMainCamera(const Camera::SPtr& camera) override;

    graphics::opengl::OpenGLContextHandle contextHandle() const {
        return gl_context_;
    }

    const graphics::Device& device() const { return *device_; }

private:
    system::ThreadPool::SPtr render_thread_;

    graphics::WindowHandle window_handle_;

    graphics::opengl::OpenGLContextHandle gl_context_;

    std::shared_ptr<graphics::opengl::OpenGLDevice> device_;

    std::mutex camera_list_mutex_;

    Vector<Camera*> camera_list_;

    Camera::SPtr main_camera_;
};
}
}
}

#endif  // GUARD_ab57776103ba468a9fbe45fc77a11914
