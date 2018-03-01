#include "temp/render/opengl/opengl_renderer.h"

namespace temp {
namespace render {
namespace opengl {

OpenGLRenderer::OpenGLRenderer(const graphics::Device::SPtr&   device,
                               const system::ThreadPool::SPtr& render_thread)
    : render_thread_(render_thread) {
    using namespace graphics;
    using namespace graphics::opengl;
    
    device_ = std::dynamic_pointer_cast<graphics::opengl::OpenGLDevice>(device);

    gl_context_ = device_->renderContext();

    auto future = render_thread_->pushJob(
        [this] { makeCurrent(window_handle_, gl_context_); });

    future.wait();
}

OpenGLRenderer::~OpenGLRenderer() {}

void OpenGLRenderer::render() {}

Camera::SPtr OpenGLRenderer::createCamera() { return nullptr; }

void OpenGLRenderer::setMainCamera(const Camera::SPtr& camera) {
    main_camera_ = camera;
}
}
}
}
