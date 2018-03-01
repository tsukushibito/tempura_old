#include "temp/render/renderer.h"

#include "temp/render/opengl/opengl_renderer.h"

namespace temp {
namespace render {

Renderer::SPtr createRenderer(const graphics::Device::SPtr& device,
                              system::ThreadPool::SPtr render_thread,
                              system::ThreadPool::SPtr worker_thread) {
    using namespace graphics;
    
    auto api = device->api();

    switch (api) {
    case GraphicsAPI::kOpenGL:
        return opengl::OpenGLRenderer::makeShared(device, render_thread);
    case GraphicsAPI::kVulkan:
    case GraphicsAPI::kD3D11:
    case GraphicsAPI::kD3D12:
    case GraphicsAPI::kMetal:
    default:
        TEMP_ASSERT(false, "");
    }

	return nullptr;
}
}
}
