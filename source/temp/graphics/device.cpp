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
#include "temp/graphics/d3d11/device_d3d11.h"
#elif defined TEMP_GRAPHICS_OPENGL
#include "temp/graphics/opengl/device_impl_opengl.h"
#endif

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

Device::VertexShaderSPtr Device::createVertexShaderFromSource(const String &source) {
	return impl_->createVertexShaderFromSource(source);
}

Device::VertexShaderSPtr Device::createVertexShaderFromBinary(const String &binary) {
	return impl_->createVertexShaderFromBinary(binary);
}

Device::PixelShaderSPtr Device::createPixelShaderFromSource(const String &source) {
	return impl_->createPixelShaderFromSource(source);
}

Device::PixelShaderSPtr Device::createPixelShaderFromBinary(const String &binary) {
	return impl_->createPixelShaderFromBinary(binary);
}
    
} // namespace graphics
} // namespace temp

