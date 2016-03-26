/**
 * @file device_impl_opengl.h
 * @brief opengl graphics device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-28
 */
#pragma once
#ifndef GUARD_fe71dbd70e5c46bca52dfc7c608632dd
#define GUARD_fe71dbd70e5c46bca52dfc7c608632dd

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/device.h"

#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics {

class Device::Impl {
    friend class Device;
private:
    Impl(Device &device);
    ~Impl();
	Impl &operator= (const Impl&) = delete;

	ContextSPtr createContext();

	VertexBufferSPtr createVertexBuffer(Size buffer_size);

	IndexBufferSPtr createIndexBuffer(Size buffer_size);

	ConstantBufferSPtr createConstantBuffer(Size buffer_size);
 
    VertexShaderSPtr createVertexShaderFromSource(const String &source);
    VertexShaderSPtr createVertexShaderFromBinary(const String &binary);

    PixelShaderSPtr createPixelShaderFromSource(const String &source);
    PixelShaderSPtr createPixelShaderFromBinary(const String &binary);

	ShaderProgramSPtr createShaderProgram(const VertexShaderSPtr &vertex_shader, const PixelShaderSPtr &pixel_shader);

	void executeCommands(const ContextSPtr &context);
	void present();	// ‰¼
private:
    Device &device_;
    opengl::OpenglContexts contexts_;
};
    
} // namespace graphics
} // namespace temp
#endif // TEMP_GRAPHICS_OPENGL
#endif // GUARD_fe71dbd70e5c46bca52dfc7c608632dd
