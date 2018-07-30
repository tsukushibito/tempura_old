/**
 * @file device_impl_opengl.cpp
 * @brief opengl graphics device
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-28
 */

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/system/thread_pool.h"
#include "temp/system/window.h"

#include "temp/graphics_old/device.h"
#include "temp/graphics_old/opengl/device_impl_opengl.h"
#include "temp/graphics_old/opengl/opengl_common.h"

#include "temp/graphics_old/blend_state.h"
#include "temp/graphics_old/depth_stencile_state.h"
#include "temp/graphics_old/pixel_shader.h"
#include "temp/graphics_old/rasterizer_state.h"
#include "temp/graphics_old/vertex_shader.h"

namespace temp {
namespace graphics_old {

Device::Impl::Impl(Device& device) : device_(device) {
    auto&& param  = device_.parameter_;
    auto&& window = param.window;
    auto&& worker = param.worker_thread;
}

Device::Impl::~Impl() {
    // opengl::deleteContexts(contexts_);   //
    // ウィンドウ削除後に呼び出されるとエラーとなるため、一旦明示的に破棄は行わない
}

Device::ContextSPtr Device::Impl::createContext() { return nullptr; }

void Device::Impl::executeCommands(const Device::ContextSPtr& context) {}

void Device::Impl::present() {
}

}  // namespace graphics
}  // namespace temp
#endif
