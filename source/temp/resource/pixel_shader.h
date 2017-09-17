/**
 * @file pixel_shader.h
 * @brief 
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-09-03
 */
#pragma once
#ifndef GUARD_5cfc562c9a8142219fbcabd8f1becc57
#define GUARD_5cfc562c9a8142219fbcabd8f1becc57
#include "temp/resource/resource_base.h"

#include "temp/graphics/graphics.h"

namespace temp {
namespace resource {

class PixelShader : public ResourceBase<PixelShader> {
    friend class ResourceBase<PixelShader>;

    using Super = ResourceBase<PixelShader>;

public:
    static void initialize(const system::ThreadPool::SPtr& loading_thread,
                           const graphics::Device::SPtr&   device);

    static void terminate();

private:
    static temp::graphics::Device::SPtr s_graphics_device;

    static const String kTypeName;

private:
    PixelShader(const system::Path& path, Bool is_binary = false);

    void deserialize(std::ifstream& ifs);
    void serialize(std::ofstream& ofs);

public:
    temp::graphics::PixelShaderSPtr pixelShader() const { return pixel_shader_; }

private:
    Bool is_binary_ = false;
    temp::graphics::PixelShaderSPtr pixel_shader_;
};
}
}
#endif // GUARD_5cfc562c9a8142219fbcabd8f1becc57
