/**
 * @file graphics_device.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-04-14
 */
#pragma once
#ifndef GUARD_26843f46d22e44879c2217ecac793e6b
#define GUARD_26843f46d22e44879c2217ecac793e6b

#include "temp/graphics/graphics.h"

namespace temp {
namespace resource {

class GraphicsDevice {
private:
    GraphicsDevice() = delete;

public:
    static void initialize(const temp::graphics::Device::SPtr& device) {
        s_device = device;
    }

    static temp::graphics::Device& get() { return *s_device; }

private:
    static temp::graphics::Device::SPtr s_device;
};
}
}

#endif  // GUARD_26843f46d22e44879c2217ecac793e6b
