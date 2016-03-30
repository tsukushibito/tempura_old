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

#define V(x) {auto hr = x; if(FAILED(hr)) { system::ConsoleLogger::error(#x " failed!({0:#x})", (unsigned long)hr); } }

namespace temp {
namespace graphics {

Device::Impl::Impl(Device &device) : device_(device) {
    auto &&param = device_.parameter_;
    auto &&window = param.window;
    
	// デバイスとコンテキストの作成
	UINT flag = 0;
	D3D_FEATURE_LEVEL level;
#ifdef DEBUG
	flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	ID3D11Device *raw_device = nullptr;
	ID3D11DeviceContext *raw_context = nullptr;
	V(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, flag, NULL, 0, D3D11_SDK_VERSION, &raw_device, &level, &raw_context));
	d3d_device_.reset(raw_device);
	d3d_context_.reset(raw_context);
    

	// スワップチェインの作成
	IDXGIFactory *raw_factory = nullptr;
	V(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&raw_factory));
	d3d11::com_unique_ptr<IDXGIFactory> dxgi_factory(raw_factory);

	DXGI_SWAP_CHAIN_DESC swap_chain_desc;
	swap_chain_desc.BufferDesc.Width = static_cast<UINT>(window->getWidth());
	swap_chain_desc.BufferDesc.Height = static_cast<UINT>(window->getHeight());
	swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0U;
	swap_chain_desc.BufferDesc.RefreshRate.Denominator = 0U;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_CENTERED;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	swap_chain_desc.BufferCount = 2;
	swap_chain_desc.OutputWindow = static_cast<HWND>(window->getWindowHandle().pointer_);
	swap_chain_desc.Windowed = TRUE;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap_chain_desc.Flags = 0;
	IDXGISwapChain *temp_swap_chain;
	V(dxgi_factory->CreateSwapChain(d3d_device_.get(), &swap_chain_desc, &temp_swap_chain));
	dxgi_swap_chain_.reset(temp_swap_chain);

	ID3D11Texture2D *temp_back_buffer = nullptr;
	V(dxgi_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&temp_back_buffer));
	d3d11::com_unique_ptr<ID3D11Texture2D> back_buffer(temp_back_buffer);

	ID3D11RenderTargetView *temp_render_target_view = nullptr;
	V(d3d_device_->CreateRenderTargetView(back_buffer.get(), NULL, &temp_render_target_view));
	d3d11::com_unique_ptr<ID3D11RenderTargetView> render_target_view(temp_render_target_view);

	d3d_context_->OMSetRenderTargets(1, render_target_view.get_pp(), NULL);

	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<FLOAT>(window->getWidth());
	viewport.Height = static_cast<FLOAT>(window->getHeight());
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 0.0f;
	d3d_context_->RSSetViewports(1, &viewport);

	device_.native_handle_.pointer_ = d3d_device_.get();
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

void Device::Impl::present() {
	// 動作確認用
	ID3D11RenderTargetView *render_target = nullptr;
	d3d_context_->OMGetRenderTargets(1, &render_target, NULL);
	static FLOAT clear_color[] = { 0.0f, 0.5f, 0.5f, 1.0f };
	d3d_context_->ClearRenderTargetView(render_target, clear_color);
	render_target->Release();
	dxgi_swap_chain_->Present(0, 0);
}

} // namespace graphics
} // namespace temp
#endif // TEMP_PLATFORM_WINDOWS
