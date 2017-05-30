/**
 * @file texture.cpp
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-04-21
 */
#include "temp/resource/texture.h"
#include "temp/resource/graphics_device.h"

namespace temp {
namespace resource {

graphics::DeviceSPtr g_graphics_device;

void Texture::initialize(const graphics::DeviceSPtr& device) {
    g_graphics_device = device;
}

void Texture::terminate() {
    Super::terminate();
    g_graphics_device = nullptr;
}

Texture::Texture(const system::Path& path) : ResourceBase<Texture>(path) {}

void Texture::loginImpl() {
    auto&& byte_data = byteData();
    g_graphics_device->createTexture();
}
}
}
