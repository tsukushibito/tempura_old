/**
 * @file device_opengl.cpp
 * @brief opengl graphics device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-28
 */

#include "temp/graphics/device.h"

namespace temp {
namespace graphics {

void Device::initialize() {
}

void Device::terminate() {
}

Device::SPtr Device::create() {
    struct Creator : public Device {
    };

    auto ptr = std::make_shared<Creator>();
    return std::move(ptr);
}
    
} // namespace graphics
} // namespace temp
