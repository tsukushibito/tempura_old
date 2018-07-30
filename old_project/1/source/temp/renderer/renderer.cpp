#include "temp/renderer/renderer.h"

namespace temp {
namespace renderer {

Renderer::Renderer(const core::ThreadPool::SPtr& render_thread,
                   const graphics::Device::SPtr& graphics_device)
    : render_thread_(render_thread), graphics_device_(graphics_device) {}
}  // namespace renderer
}  // namespace temp