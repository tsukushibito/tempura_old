/**
 * @file device.cpp
 * @brief graphics device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-29
 */
#include <new>

#include "temp/define.h"
#include "temp/type.h"

#include "temp/system/thread_pool.h"

#include "temp/graphics/device.h"
#if defined TEMP_GRAPHICS_D3D11
#include "temp/graphics/d3d11/device_impl_d3d11.h"
#elif defined TEMP_GRAPHICS_OPENGL
#include "temp/graphics/opengl/device_impl_opengl.h"
#endif

#include "temp/graphics/context.h"
#include "temp/graphics/vertex_buffer.h"
#include "temp/graphics/index_buffer.h"
#include "temp/graphics/vertex_shader.h"
#include "temp/graphics/pixel_shader.h"
#include "temp/graphics/blend_state.h"
#include "temp/graphics/depth_stencile_state.h"
#include "temp/graphics/rasterizer_state.h"

namespace temp {
namespace graphics {

Device::SPtr Device::create(const DeviceParameter &param) {
    struct Creator : public Device {
        Creator(const DeviceParameter &param) 
            : Device(param)
        {};
    };

    auto ptr = std::make_shared<Creator>(param);
    return std::move(ptr);
}

Device::Device(const DeviceParameter &param) 
    : parameter_(param)
{ 
    static_assert(sizeof(Impl) <= sizeof(impl_buffer_), "size of impl_buffer_ is small.");
    impl_ = new(impl_buffer_) Impl(*this);
}

Device::~Device() {
    // placement new でスタックに領域を確保しているので明示的にデストラクタを呼び出す
    impl_->~Impl(); 
    parameter_.main_thread = nullptr;
}

Device::ContextSPtr Device::createContext() {
    return Context::create(native_handle_);
}

Device::VertexBufferSPtr Device::createVertexBuffer(Size size, const void *data) {
    return VertexBuffer::create(native_handle_, size, data);
}

Device::IndexBufferSPtr Device::createIndexBuffer(Size size, const void *data) {
    return IndexBuffer::create(native_handle_, size, data);
}

Device::VertexShaderSPtr Device::createVertexShaderFromSource(const String &source) {
    return VertexShader::create(native_handle_, source, false);
}

Device::VertexShaderSPtr Device::createVertexShaderFromBinary(const String &binary) {
    return VertexShader::create(native_handle_, binary, true);
}

Device::PixelShaderSPtr Device::createPixelShaderFromSource(const String &source) {
    return PixelShader::create(native_handle_, source, false);
}

Device::PixelShaderSPtr Device::createPixelShaderFromBinary(const String &binary) {
    return PixelShader::create(native_handle_, binary, true);
}
    
Device::BlendStateSPtr Device::createBlendState(BlendMode blend_mode) {
    return BlendState::create(native_handle_, blend_mode);
}

Device::DepthStencileStateSPtr Device::createDepthStencileState(DepthStencileFunc depth_func, DepthStencileFunc stencile_func) {
    return DepthStencileState::create(native_handle_, depth_func, stencile_func);
}

Device::RasterizerStateSPtr Device::createRasterizerState(const RasterizerDesc &desc) {
    return RasterizerState::create(native_handle_, desc);
}

void Device::present() {
    return impl_->present();
}
    
} // namespace graphics
} // namespace temp

