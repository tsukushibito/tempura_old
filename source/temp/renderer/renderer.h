#pragma once
#include "temp/common/common.h"
#include "temp/core/core.h"
#include "temp/graphics/graphics.h"

namespace temp {
namespace renderer {
class Renderer : public SmartPointerObject<Renderer> {
 public:
  Renderer(const core::ThreadPool::SPtr& render_thread,
           const graphics::Device::SPtr& graphics_device);

 private:
  core::ThreadPool::SPtr render_thread_;
  graphics::Device::SPtr graphics_device_;
};
}  // namespace renderer
}  // namespace temp