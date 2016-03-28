/**
 * @file pixel_shader_resource.cpp
 * @brief pixel shader resource
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-29
 */

#include "temp/resource/pixel_shader_resource.h"

namespace temp {
namespace resource {

PixelShaderResource::PixelShaderResource(const system::Path &path) 
    : ResourceBase<PixelShaderResource>(path) {
}

void PixelShaderResource::loginImpl() {
    pixel_shader_ = s_graphics_device->createPixelShaderFromSource(buffer_);
}
    
} // namespace resource
} // namespace temp
