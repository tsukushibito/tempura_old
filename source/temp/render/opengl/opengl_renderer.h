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

#include "temp/graphics/graphics.h"

#include "temp/resource/pixel_shader.h"
#include "temp/resource/vertex_shader.h"

#include "temp/render/renderer.h"

#include "temp/render/opengl/opengl_copy_to_backbuffer.h"

namespace temp {
namespace render {

class Renderer::Impl {
public:
    explicit Impl(Renderer& renderer);
    ~Impl();

    Renderer::RenderTargetSPtr createRenderTarget(
        const graphics::RenderTargetDesc& desc);

    void render();

    void onCameraDestory(Camera* camera);

private:
    void renderView(Camera* camera);

    void copyToBackBuffer();

private:
    struct FboAndDepthBuffer {
        GLuint fbo;
        GLuint depth_buffer;
    };

    Renderer& renderer_;

    temp::graphics::opengl::OpenGLContextHandle gl_context_;

    std::future<void> prev_frame_render_job_;

    HashMap<Camera*, FboAndDepthBuffer> fbo_table_;

    GLuint sampler_table_[(Int32)temp::graphics::SamplerFilter::COUNT]
                         [(Int32)temp::graphics::SamplerAddressMode::COUNT];

    std::unique_ptr<opengl::CopyToBackBuffer> copyToBackBuffer_;

    GLuint debug_tex_;
};
}
}

#endif  // GUARD_863b2c1cae9d409a8153998397747e60
