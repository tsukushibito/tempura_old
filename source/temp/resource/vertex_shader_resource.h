/**
 * @file vertex_shader_resource.h
 * @brief vertex shader resource
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-28
 */
#pragma once
#ifndef GUARD_64bef9fa34394904a86f76b33d413d66
#define GUARD_64bef9fa34394904a86f76b33d413d66

#include "temp/graphics/vertex_shader.h"
#include "temp/resource/resource_base.h"

namespace temp {
namespace resource {

class VertexShader : public ResourceBase<VertexShader> {
    friend class ResourceBase<VertexShader>;
private:
    VertexShader(const system::Path &path);

public:
	graphics::VertexShader::SPtr get() const { return vertex_shader_; }

private:
    void loginImpl();
    void logoutImpl();

    graphics::VertexShader::SPtr vertex_shader_;
};
    
} // namespace resource
} // namespace temp

#endif // GUARD_64bef9fa34394904a86f76b33d413d66
