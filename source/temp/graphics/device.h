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

class Device : public SmartPointerObject<Device> {
public:
	using ThreadPoolSPtr = std::shared_ptr<system::ThreadPool>;

    static SPtr create(const ThreadPoolSPtr &render_thread, const ThreadPoolSPtr &load_thread);

private:
    Device(const ThreadPoolSPtr &render_thread, const ThreadPoolSPtr &load_thread);

private:
	class Impl;
    union ImplBuffer {
        Int8 buffer_[kImplSize];
        void *pointer_;
    };

    ImplBuffer impl_buffer_;
	Impl *impl_;

	ThreadPoolSPtr render_thread_;
	ThreadPoolSPtr load_thread_;
};
    
} // namespace graphics
} // namespace temp

#endif // GUARD_0a9808d4fbc94cccacebb5e8b0091b80
