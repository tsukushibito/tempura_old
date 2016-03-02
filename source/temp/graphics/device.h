/**
 * @file device.h
 * @brief graphics device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-28
 */
#pragma once
#ifndef GUARD_0a9808d4fbc94cccacebb5e8b0091b80
#define GUARD_0a9808d4fbc94cccacebb5e8b0091b80

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics/graphics_common.h"

namespace temp {
namespace system {
class ThreadPool;
}
}

namespace temp {
namespace graphics {

struct DeviceParameter {
	std::shared_ptr<system::ThreadPool> render_thread;
	std::shared_ptr<system::ThreadPool> load_thread;
};

class Device : public SmartPointerObject<Device> {
public:
    static SPtr create(const DeviceParameter &parameter);

private:
    Device(const DeviceParameter &parameter);

private:
	class Impl;
    union ImplBuffer {
        Int8 buffer_[kImplSize];
        void *pointer_;
    };

    ImplBuffer impl_buffer_;
	Impl *impl_;

	DeviceParameter parameter_;
};
    
} // namespace graphics
} // namespace temp

#endif // GUARD_0a9808d4fbc94cccacebb5e8b0091b80
