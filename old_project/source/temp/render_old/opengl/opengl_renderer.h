/**
 * @file opengl_renderer.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-08-21
 */
#pragma once
#ifndef GUARD_863b2c1cae9d409a8153998397747e60
#define GUARD_863b2c1cae9d409a8153998397747e60

#include "temp/temp_math.h"

#include "temp/graphics_/graphics.h"

#include "temp/resource_old/pixel_shader.h"
#include "temp/resource_old/vertex_shader.h"

#include "temp/render_old/renderer.h"

#include "temp/render_old/opengl/opengl_copy_to_backbuffer.h"

namespace temp {
namespace render_old {

class Renderer::Impl {
public:
    explicit Impl(Renderer& renderer);
    ~Impl();

    Renderer::RenderTargetSPtr createRenderTarget(
        const graphics_::RenderTargetDesc& desc);

    void render();

    void onCameraCreate(Camera* camera);
    void onCameraDestory(Camera* camera);

private:
    void renderView(Camera* camera);

private:
    struct FboAndDepthBuffer {
        GLuint fbo;
        GLuint depth_buffer;
    };

    Renderer& renderer_;

    temp::graphics_::opengl::OpenGLContextHandle gl_context_;

    std::future<void> prev_frame_render_job_;

    HashMap<Camera*, FboAndDepthBuffer> fbo_table_;

    GLuint sampler_table_[(Int32)temp::graphics_::SamplerFilter::COUNT]
                         [(Int32)temp::graphics_::SamplerAddressMode::COUNT];

    std::unique_ptr<opengl::CopyToBackBuffer> copyToBackBuffer_;

    GLuint debug_tex_;
    GLuint debug_vertices_;
    GLuint debug_vao_;
};
}
}

#endif  // GUARD_863b2c1cae9d409a8153998397747e60
