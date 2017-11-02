/**
 * @file vertex_shader.cpp
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-08-25
 */
#include "temp/resource_old/vertex_shader.h"

#include "temp/graphics_/graphics.h"

namespace temp {
namespace resource_old {

temp::graphics_::Device::SPtr VertexShader::s_graphics_device;

const temp::String VertexShader::kTypeName = "VertexShader";

void VertexShader::initialize(const system::ThreadPool::SPtr& loading_thread,
                              const graphics_::DeviceSPtr&     device) {
    Super::initialize(loading_thread);
    s_graphics_device = device;
}

void VertexShader::terminate() {
    Super::terminate();
    s_graphics_device = nullptr;
}

VertexShader::VertexShader(const system::Path& path, Bool is_binary)
    : Super(path), is_binary_(is_binary) {}

void VertexShader::deserialize(std::ifstream& ifs) {
    // using temp::system::Logger;

    std::istreambuf_iterator<char> it(ifs);
    std::istreambuf_iterator<char> last;
    graphics_::ShaderCode code;
    code.code_ = String(it, last);
    code.is_binary_ = is_binary_;

    vertex_shader_ = s_graphics_device->createVertexShader(code);
}

void VertexShader::serialize(std::ofstream& ofs) {
    auto &&code = vertex_shader_->code();
    ofs.write((char*)&code.code_[0], code.code_.size());
}
    
}
}
