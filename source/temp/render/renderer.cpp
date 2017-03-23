#include <functional>
#include "temp/temp_assert.h"
#include "temp/graphics/device.h"
#include "temp/render/renderer.h"

namespace temp {
namespace render {

Renderer::Renderer(const graphics_old::DeviceSPtr &graphics_device) : device_(graphics_device) {
    clear_vs_res_ = resource::VertexShaderResource::create("shader/glsl/clear_glsl.vert");
    clear_vs_res_->load();
    clear_ps_res_ = resource::PixelShaderResource::create("shader/glsl/clear_glsl.frag");
    clear_ps_res_->load();
}

Renderer::SPtr Renderer::create(const graphics_old::DeviceSPtr &graphics_device) {
    struct Creator : public Renderer {
        Creator(const graphics_old::DeviceSPtr &graphics_device)
            : Renderer(graphics_device) {
        }
    };

    auto ptr = std::make_shared<Creator>(graphics_device);
    return std::move(ptr);
}

void Renderer::renderAllViews() {
}

void Renderer::swapBackBuffers() {
    device_->present();
}


}
}
