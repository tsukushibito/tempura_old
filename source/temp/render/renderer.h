/**
 * @file renderer.h
 * @brief renderer
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-18
 */
#pragma once
#ifndef GUARD_0c103a63ba65427bbd196ab3610f2b5e
#define GUARD_0c103a63ba65427bbd196ab3610f2b5e

#include "temp/type.h"

namespace temp {
namespace graphics {
class Device; 
using DeviceSPtr = std::shared_ptr<Device>;
} // namespace graphics
} // namespace temp

namespace temp {
namespace render {

class Renderer : public SmartPointerObject<Render> {
private:
    Renderer(const DeviceSPtr &graphics_device);

private:
    DeviceSPtr device_;
};
    
} // namespace render
} // namespace temp

#endif // GUARD_0c103a63ba65427bbd196ab3610f2b5e
