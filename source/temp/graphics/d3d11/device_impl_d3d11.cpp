/**
 * @file device_impl_d3d11.cpp
 * @brief d3d11 device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-24
 */
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_D3D11
#include "temp/system/logger.h"
#include "temp/system/window.h"

#include "temp/graphics/device.h"
#include "temp/graphics/d3d11/device_impl_d3d11.h"

#include "temp/graphics/vertex_shader.h"

namespace temp {
namespace graphics {

Device::Impl::Impl(Device &device) : device_(device) {
    auto &&param = device_.parameter_;
    auto &&window = param.window;
    auto &&worker = param.worker_thread;
    
	UINT flag = 0;
	D3D_FEATURE_LEVEL level;
#ifdef DEBUG
	flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	auto hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flag, NULL, 0, D3D11_SDK_VERSION, &d3d_device_, &level, &d3d_context_);
	if (FAILED(hr)) {
		system::ConsoleLogger::error("D3D11CreateDevice failed!({0})", hr);
	}
    
	IDXGIFactory *dxgi_factory = nullptr;
	hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&dxgi_factory);
	if (FAILED(hr)) {
		system::ConsoleLogger::error("CreateDXGIFactory failed!({0})", hr);
	}

    // DXGI_MODE_DESC BufferDesc;
    // DXGI_SAMPLE_DESC SampleDesc;
    // DXGI_USAGE BufferUsage;
    // UINT BufferCount;
    // HWND OutputWindow;
    // BOOL Windowed;
    // DXGI_SWAP_EFFECT SwapEffect;
    // UINT Flags;

    // UINT Width;
    // UINT Height;
    // DXGI_RATIONAL RefreshRate;
    // DXGI_FORMAT Format;
    // DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
    // DXGI_MODE_SCALING Scaling;
	DXGI_SWAP_CHAIN_DESC swap_chain_desc = {
		{ window->getWidth(), window->getHeight(), {0U, 0U}, DXGI_FORMAT},
		{},
	};
	dxgi_factory->CreateSwapChain(d3d_device_, &swap_chain_desc, &dxgi_swap_chain_);
}

Device::Impl::~Impl() {
}

Device::VertexShaderSPtr Device::Impl::createVertexShaderFromSource(const String &source) {
    return nullptr;
}

Device::VertexShaderSPtr Device::Impl::createVertexShaderFromBinary(const String &binary) {
    return nullptr;
}

Device::PixelShaderSPtr Device::Impl::createPixelShaderFromSource(const String &source) {
    return nullptr;
}

Device::PixelShaderSPtr Device::Impl::createPixelShaderFromBinary(const String &binary) {
    return nullptr;
}

} // namespace graphics
} // namespace temp
#endif // TEMP_PLATFORM_WINDOWS
