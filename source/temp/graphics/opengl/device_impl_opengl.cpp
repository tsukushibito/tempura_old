/**
 * @file device_impl_opengl.cpp
 * @brief opengl graphics device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-28
 */

#include "temp/graphics/device.h"
#include "temp/graphics/opengl/device_impl_opengl.h"

namespace temp {
namespace graphics {

Device::Impl::Impl(Device *device) : device_(device) {
}

Device::Impl::~Impl() {
}
    
} // namespace graphics
} // namespace temp
