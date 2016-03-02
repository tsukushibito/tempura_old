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

Device::SPtr Device::create(const ThreadPoolSPtr &render_thread, const ThreadPoolSPtr &load_thread) {
    struct Creator : public Device {
		Creator(const ThreadPoolSPtr &render_thread, const ThreadPoolSPtr &load_thread) 
			: Device(render_thread, load_thread)
		{};
    };

    auto ptr = std::make_shared<Creator>(render_thread, load_thread);
    return std::move(ptr);
}

Device::Device(const ThreadPoolSPtr &render_thread, const ThreadPoolSPtr &load_thread) 
	: render_thread_(render_thread)
	, load_thread_(load_thread)
{ 
	impl_ = new(impl_buffer_.pointer_) Impl;
}
    
} // namespace graphics
} // namespace temp

