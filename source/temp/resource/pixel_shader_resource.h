#pragma once
/**
 * @file pixel_shader_resource.h
 * @brief pixel shader resource
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-29
 */
#ifndef GUARD_7fc393d9de364368879b6e84c0a1dee5
#define GUARD_7fc393d9de364368879b6e84c0a1dee5

#include "temp/graphics/pixel_shader.h"
#include "temp/resource/resource_base.h"

namespace temp {
namespace resource {

class PixelShaderResource : public ResourceBase<PixelShaderResource> {
    friend class ResourceBase<PixelShaderResource>;
private:
    PixelShaderResource(const system::Path &path);

public:
    graphics::PixelShader::SPtr get() const { return pixel_shader_; }

private:
    void loginImpl();

    graphics::PixelShader::SPtr pixel_shader_;
};
   
} // namespace resource 
} // namespace temp

#endif // GUARD_7fc393d9de364368879b6e84c0a1dee5
