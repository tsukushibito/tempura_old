/**
 * @file vertex_shader.h
 * @brief 
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-08-25
 */
#pragma once
#ifndef GUARD_6cfec183decb4aa9bb6a2aa8921498d8
#define GUARD_6cfec183decb4aa9bb6a2aa8921498d8
#include "temp/resource/resource_base.h"

#include "temp/graphics/graphics.h"

namespace temp {
namespace resource {

class VertexShader : public ResourceBase<VertexShader> {
    friend class ResourceBase<VertexShader>;

    using Super = ResourceBase<VertexShader>;

public:
    static void initialize(const system::ThreadPool::SPtr& loading_thread,
                           const graphics::Device::SPtr&   device);

    static void terminate();

private:
    static temp::graphics::Device::SPtr s_graphics_device;

    static const String kTypeName;

private:
    VertexShader(const system::Path& path, Bool is_binary = false);

    void deserialize(std::ifstream& ifs);
    void serialize(std::ofstream& ofs);

public:
    temp::graphics::VertexShaderSPtr vertexShader() const { return vertex_shader_; }

private:
    Bool is_binary_ = false;
    temp::graphics::VertexShaderSPtr vertex_shader_;
};

}
}
#endif // GUARD_6cfec183decb4aa9bb6a2aa8921498d8
