/**
 * @file opengl_renderer.mm
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-08-21
 */

#include "temp/graphics/graphics.h"
#include "temp/graphics/opengl/opengl_common.h"
#if defined(TEMP_PLATFORM_MAC)
#include "temp/graphics/opengl/mac/opengl_mac.h"
#elif defined(TEMP_PLATFORM_WINDOWS)
#include "temp/graphics/opengl/windows/opengl_windows.h"
#endif

#include "temp/temp_assert.h"

// #include "temp/system/logger.h"

#include "temp/render/opengl/opengl_renderer.h"

namespace temp {
namespace render {

Renderer::Impl::Impl(Renderer& renderer) : renderer_(renderer) {
    using namespace temp::graphics;
    using namespace temp::graphics::opengl;

    OpenGLContextHandle context = renderer.graphics_device_->nativeHandle();
    gl_context_ = temp::graphics::opengl::createSharedContext(context);

    auto job = renderer_.render_thread_->pushJob([this]() {
        makeCurrent(gl_context_);

        GLsizei sampler_count = (GLsizei)SamplerFilter::COUNT
                                * (GLsizei)SamplerAddressMode::COUNT;
        glCallWithErrorCheck(glGenSamplers, sampler_count,
                             (GLuint*)&sampler_table_);

        GLenum gl_min_filter_table[(Int32)SamplerFilter::COUNT] = {
            // GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_LINEAR,
            GL_NEAREST, GL_LINEAR,
        };
        GLenum gl_mag_filter_table[(Int32)SamplerFilter::COUNT] = {
            GL_NEAREST, GL_LINEAR,
        };
        GLenum gl_address_table[(Int32)SamplerAddressMode::COUNT] = {
            GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER,
        };

        for (Int32 filter = 0; filter < (Int32)SamplerFilter::COUNT; ++filter) {
            for (Int32 address = 0; address < (Int32)SamplerAddressMode::COUNT;
                 ++address) {
                auto sampler       = sampler_table_[filter][address];
                auto gl_min_filter = gl_min_filter_table[filter];
                auto gl_mag_filter = gl_mag_filter_table[filter];
                auto gl_address    = gl_address_table[address];
                glCallWithErrorCheck(glSamplerParameteri, sampler,
                                     GL_TEXTURE_MIN_FILTER, gl_min_filter);
                glCallWithErrorCheck(glSamplerParameteri, sampler,
                                     GL_TEXTURE_MAG_FILTER, gl_mag_filter);
                glCallWithErrorCheck(glSamplerParameteri, sampler,
                                     GL_TEXTURE_WRAP_R, gl_address);
                glCallWithErrorCheck(glSamplerParameteri, sampler,
                                     GL_TEXTURE_WRAP_S, gl_address);
                glCallWithErrorCheck(glSamplerParameteri, sampler,
                                     GL_TEXTURE_WRAP_T, gl_address);
            }
        }

        copyToBackBuffer_.reset(new opengl::CopyToBackBuffer(
            renderer_.graphics_device_, renderer_.shader_directory_));

        // クリアパラメータを設定しておく
        glCallWithErrorCheck(glClearColor, 0.0f, 0.5f, 0.5f, 1.0f);
        glCallWithErrorCheck(glClearDepth, 1.0f);
        glCallWithErrorCheck(glClearStencil, 0);

        glCallWithErrorCheck(glGenTextures, 1, &debug_tex_);
        glCallWithErrorCheck(glBindTexture, GL_TEXTURE_2D, debug_tex_);
        UInt8 debug_data[4 * 4];
        for (auto&& p : debug_data) {
            p = 255;
        }
        glCallWithErrorCheck(glTexImage2D, GL_TEXTURE_2D, 0, GL_RGBA, 2, 2, 0,
                             GL_RGBA, GL_UNSIGNED_BYTE,
                             (const GLvoid*)debug_data);
        glCallWithErrorCheck(glBindTexture, GL_TEXTURE_2D, 0);
    });

    job.wait();
}

Renderer::Impl::~Impl() {
    using namespace temp::graphics;
    using namespace temp::graphics::opengl;

    if (prev_frame_render_job_.valid()) {
        prev_frame_render_job_.wait();
    }

    auto job = renderer_.render_thread_->pushJob([this]() {
        copyToBackBuffer_.reset(nullptr);

        GLsizei sampler_count = (GLsizei)SamplerFilter::COUNT
                                * (GLsizei)SamplerAddressMode::COUNT;
        glCallWithErrorCheck(glDeleteSamplers, sampler_count,
                             (GLuint*)&sampler_table_);

        for (auto key_value : fbo_table_) {
            auto depth_buffer = key_value.second.depth_buffer;
            glCallWithErrorCheck(glDeleteRenderbuffers, 1, &depth_buffer);
            auto fbo = key_value.second.fbo;
            glCallWithErrorCheck(glDeleteFramebuffers, 1, &fbo);
        }
    });

    job.wait();

    renderer_.render_thread_->pushJob([this]() {

    });

    while (!renderer_.render_thread_->jobEmpty()) {
    }

    temp::graphics::opengl::deleteContext(gl_context_);
}

Renderer::RenderTargetSPtr Renderer::Impl::createRenderTarget(
    const RenderTargetDesc& desc) {
    return renderer_.graphics_device_->createRenderTarget(desc);
}

void Renderer::Impl::render() {
    using namespace temp::graphics;
    using namespace temp::graphics::opengl;

    // prev_frame_render_job_.wait_for(std::chrono::seconds(1));
    if (prev_frame_render_job_.valid()) {
        prev_frame_render_job_.wait();
    }

    // auto job_count = renderer_.render_thread_->jobCount();
    // std::cout << job_count << std::endl;

    prev_frame_render_job_ = renderer_.render_thread_->pushJob([this]() {


        // glCallWithErrorCheck(glClear, GL_COLOR_BUFFER_BIT |
        // GL_DEPTH_BUFFER_BIT
        //                                   | GL_STENCIL_BUFFER_BIT);

        for (auto&& camera : renderer_.camera_list_) {
            renderView(camera);
        }

        auto main_camera = renderer_.main_camera_.lock();
        if (main_camera) {
            auto status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
            if (status != GL_FRAMEBUFFER_COMPLETE) {
                return;
            }
            auto render_target = main_camera->renderTarget();
            auto texture       = render_target->nativeHandle();
            auto sampler       = sampler_table_[(Int32)SamplerFilter::kLinear]
                                         [(Int32)SamplerAddressMode::kBorder];
            copyToBackBuffer_->copy(texture, sampler);
            // copyToBackBuffer_->copy(debug_tex_, sampler);
        }

        // glCallWithErrorCheck(glFlush);
        swapBuffers(gl_context_);
    });
}

void Renderer::Impl::renderView(Camera* camera) {
    using namespace temp::graphics::opengl;

    auto key_value = fbo_table_.find(camera);

    GLuint fbo;
    if (key_value == fbo_table_.end()) {
        // カメラに対応するFBOが未作成の場合作成する
        glCallWithErrorCheck(glGenFramebuffers, 1, &fbo);
        glCallWithErrorCheck(glBindFramebuffer, GL_FRAMEBUFFER, fbo);
        // カメラのレンダーターゲット用テクスチャをバインド
        auto render_target = camera->renderTarget();
        auto tex           = render_target->nativeHandle();
        glCallWithErrorCheck(glFramebufferTexture2D, GL_FRAMEBUFFER,
                             GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);

        // 深度バッファを作成してバインド
        GLuint depth_buffer;
        glCallWithErrorCheck(glGenRenderbuffers, 1, &depth_buffer);
        glCallWithErrorCheck(glBindRenderbuffer, GL_RENDERBUFFER, depth_buffer);
        auto desc = render_target->description();
        glCallWithErrorCheck(glRenderbufferStorage, GL_RENDERBUFFER,
                             GL_DEPTH_COMPONENT, desc.width, desc.height);

        glCallWithErrorCheck(glFramebufferRenderbuffer, GL_FRAMEBUFFER,
                             GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,
                             depth_buffer);

        // バインドしていたレンダーバッファとFBOを解放
        glCallWithErrorCheck(glBindRenderbuffer, GL_RENDERBUFFER, 0);
        glCallWithErrorCheck(glBindFramebuffer, GL_FRAMEBUFFER, 0);

        fbo_table_[camera].fbo          = fbo;
        fbo_table_[camera].depth_buffer = depth_buffer;
    } else {
        fbo = key_value->second.fbo;
    }

    glCallWithErrorCheck(glBindFramebuffer, GL_FRAMEBUFFER, fbo);

    auto status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
        glCallWithErrorCheck(glBindFramebuffer, GL_FRAMEBUFFER, 0);
        return;
    }

    glCallWithErrorCheck(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT
                                      | GL_STENCIL_BUFFER_BIT);

    glCallWithErrorCheck(glBindFramebuffer, GL_FRAMEBUFFER, 0);
}

void Renderer::Impl::copyToBackBuffer() {}

void Renderer::Impl::onCameraDestory(Camera* camera) {
    using namespace temp::graphics::opengl;

    renderer_.render_thread_->pushJob([this, camera]() {
        auto key_value = fbo_table_.find(camera);
        if (key_value == fbo_table_.end()) return;

        auto depth_buffer = key_value->second.depth_buffer;
        glCallWithErrorCheck(glDeleteRenderbuffers, 1, &depth_buffer);

        auto fbo = key_value->second.fbo;
        glCallWithErrorCheck(glDeleteFramebuffers, 1, &fbo);
        fbo_table_.erase(key_value);
    });
}
}
}
