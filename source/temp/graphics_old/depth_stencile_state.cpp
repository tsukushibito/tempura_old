/**
 * @file depth_stencile_state.cpp
 * @brief Depth Stencile State
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-23
 */

#include <new>

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics_old/depth_stencile_state.h"
#if defined   TEMP_GRAPHICS_D3D11
#elif defined TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/opengl/depth_stencile_state_impl_opengl.h"
#endif

namespace temp {
namespace graphics_old {

DepthStencileState::SPtr DepthStencileState::create(
    NativeHandle device, DepthStencileFunc depth_func,
    DepthStencileFunc stencile_func) {
    struct Creator : public DepthStencileState {
        Creator(NativeHandle device, DepthStencileFunc depth_func,
                DepthStencileFunc stencile_func)
            : DepthStencileState(device, depth_func, stencile_func) {}
    };
    auto p = std::make_shared<Creator>(device, depth_func, stencile_func);
    return std::move(p);
}

DepthStencileState::DepthStencileState(NativeHandle      device,
                                       DepthStencileFunc depth_func,
                                       DepthStencileFunc stencile_func) {
    static_assert(sizeof(Impl) <= sizeof(impl_buffer_),
                  "size of impl_buffer_ is small.");
    impl_ = new (impl_buffer_) Impl(device, *this, depth_func, stencile_func);
}

DepthStencileState::~DepthStencileState() { impl_->~Impl(); }

}  // namespace graphics
}  // namespace temp
