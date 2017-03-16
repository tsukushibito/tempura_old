/**
 * @file device.cpp
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-14
 */

#include "temp/graphics/device.h"
#include <mutex>
#include "temp/container.h"
#include "temp/graphics/opengl/opengl_device.h"

namespace temp {
namespace graphics {

namespace {
temp::Vector<DeviceHandle> g_opengl_device_table;
std::mutex                 g_opengl_device_table_mutex;
}

class Device::Impl {
public:
    explicit Impl(const temp::system::WindowHandle& window_handle)
        : opengl_device_(window_handle) {}

    const DeviceHandle& handle() const { return opengl_device_.handle(); }

    opengl::OpenGlDevice opengl_device_;
};

Device::SPtr Device::create(const temp::system::WindowHandle& window_handle) {
    struct Creator : public Device {
        Creator(const temp::system::WindowHandle& window_handle)
            : Device(window_handle) {}
    };

    return std::make_shared<Creator>(window_handle);
}

Device::Device(const temp::system::WindowHandle& window_handle)
    : impl_(new Impl(window_handle)) {}

Device::~Device() {}

DeviceHandle Device::handle() { return impl_->handle(); }
}
}
