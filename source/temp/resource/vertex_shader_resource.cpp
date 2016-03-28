/**
 * @file vertex_shader_resource.cpp
 * @brief vertex shader resource
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-28
 */

#include "temp/resource/vertex_shader_resource.h"

namespace temp {
namespace resource {

VertexShaderResource::VertexShaderResource(const system::Path &path) 
    : ResourceBase<VertexShaderResource>(path) {
}

void VertexShaderResource::loginImpl() {
    vertex_shader_ = s_graphics_device->createVertexShaderFromSource(buffer_);
}

}
}
