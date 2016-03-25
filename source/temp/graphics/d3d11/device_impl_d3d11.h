/**
 * @file device_impl_d3d11.h
 * @brief d3d11 device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-24
 */
#pragma once
#ifndef GUARD_b2437af2c6ef46ddbd33310a7ce0dc00
#define GUARD_b2437af2c6ef46ddbd33310a7ce0dc00
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_D3D11
#include <dxgi.h>
#include <d3d11.h>
#include "temp/type.h"
#include "temp/graphics/d3d11/d3d11_common.h"
#include "temp/graphics/device.h"

namespace temp {
namespace graphics {

class Device::Impl {
    friend class Device;
private:
    Impl(Device &device);
    ~Impl();
    Impl &operator= (const Impl&) = delete;

    VertexShaderSPtr createVertexShaderFromSource(const String &source);
    VertexShaderSPtr createVertexShaderFromBinary(const String &binary);

    PixelShaderSPtr createPixelShaderFromSource(const String &source);
    PixelShaderSPtr createPixelShaderFromBinary(const String &binary);

	void present();	// ‰¼
private:
    Device &device_;
	d3d11::com_unique_ptr<ID3D11Device> d3d_device_;
	d3d11::com_unique_ptr<ID3D11DeviceContext> d3d_context_;
	d3d11::com_unique_ptr<IDXGISwapChain> dxgi_swap_chain_;
};
    
} // namespace graphics
} // namespace temp

#endif
#endif // GUARD_b2437af2c6ef46ddbd33310a7ce0dc00
