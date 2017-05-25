#include <functional>
#include "temp/temp_assert.h"
#include "temp/graphics/device.h"
#include "temp/render/renderer.h"

namespace temp {
namespace render {

Renderer::Renderer(const graphics_old::DeviceSPtr &graphics_device) : device_(graphics_device) {

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

}


}
}
