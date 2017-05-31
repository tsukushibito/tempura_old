/**
 * @file texture.cpp
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-04-21
 */
#include "temp/resource/texture.h"

namespace temp {
namespace resource {

temp::graphics::DeviceSPtr Texture::s_graphics_device;

void Texture::initialize(const system::ThreadPool::SPtr& loading_thread,
                         const graphics::DeviceSPtr&     device) {
    Super::initialize(loading_thread);
    s_graphics_device = device;
}

void Texture::terminate() {
    Super::terminate();
    s_graphics_device = nullptr;
}

Texture::Texture(const system::Path& path) : Super(path) {}

void Texture::loginImpl() {
    auto&& byte_data = byteData();
    // g_graphics_device->createTexture();
}
}
}
