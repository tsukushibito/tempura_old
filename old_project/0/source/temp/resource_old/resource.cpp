/**
 * @file resource.cpp
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-05
 */


#include "temp/resource_old/resource.h"

namespace temp {
namespace resource_old {
void initialize(const system::ThreadPool::SPtr& loading_thread,
                const graphics_::Device::SPtr&   device) {
    Material::initialize(loading_thread);
    Mesh::initialize(loading_thread, device);
    PixelShader::initialize(loading_thread, device);
    Texture::initialize(loading_thread, device);
    VertexShader::initialize(loading_thread, device);
}

void terminate() {
    Material::terminate();
    Mesh::terminate();
    PixelShader::terminate();
    Texture::terminate();
    VertexShader::terminate();
}
}
}
