/**
 * @file shader_program.h
 * @brief shader program
 *  D3DのEffect、OpenGLのProgramに相当
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-29
 */
#pragma once
#ifndef GUARD_de943ada63f94238b15078213f27b1e0
#define GUARD_de943ada63f94238b15078213f27b1e0

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics_old/graphics_common.h"

namespace temp {
namespace graphics {

class VertexShader;
class PixelShader;

class ShaderProgram : public SmartPointerObject<ShaderProgram>,
                      public FastPImpl {
    friend class Device;

public:
    using VertexShaderSPtr = std::shared_ptr<VertexShader>;
    using PixelShaderSPtr  = std::shared_ptr<PixelShader>;

private:
    ShaderProgram(const NativeHandle& native_handle);

public:
    ~ShaderProgram();

    VertexShaderSPtr    getVertexShader() const { return vertex_shader_; }
    PixelShaderSPtr     getPixelShader() const { return pixel_shader_; }
    const NativeHandle& getNativeHandle() const { return native_handle_; }

private:
    class Impl;
    Impl* impl_;

    VertexShaderSPtr vertex_shader_;
    PixelShaderSPtr  pixel_shader_;
    NativeHandle     native_handle_;
};

}  // namespace graphics
}  // namespace temp
#endif  // GUARD_de943ada63f94238b15078213f27b1e0
