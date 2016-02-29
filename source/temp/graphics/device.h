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
namespace graphics {

class Device : public SmartPointerObject<Device> {
public:
    static void initialize();
    static void terminate();
    static SPtr create();

private:
    Device();

private:
    union ImplBuffer {
        Int8 buffer_[kImplSize];
        void *pointer_;
    };

    ImplBuffer impl_buffer_;
};
    
} // namespace graphics
} // namespace temp

#endif // GUARD_0a9808d4fbc94cccacebb5e8b0091b80
