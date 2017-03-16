/**
 * @file rasterizer_state.cpp
 * @brief Rasterizer State
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-24
 */

#include <new>

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics_old/rasterizer_state.h"
#if defined   TEMP_GRAPHICS_D3D11
#elif defined TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/opengl/rasterizer_state_impl_opengl.h"
#endif

namespace temp {
namespace graphics_old {

RasterizerState::SPtr RasterizerState::create(NativeHandle          device,
                                              const RasterizerDesc& desc) {
    struct Creator : public RasterizerState {
        Creator(NativeHandle device, const RasterizerDesc& desc)
            : RasterizerState(device, desc) {}
    };
    auto p = std::make_shared<Creator>(device, desc);
    return std::move(p);
}

RasterizerState::RasterizerState(NativeHandle          device,
                                 const RasterizerDesc& desc) {
    static_assert(sizeof(Impl) <= sizeof(impl_buffer_),
                  "size of impl_buffer_ is small.");
    impl_ = new (impl_buffer_) Impl(device, *this, desc);
}

RasterizerState::~RasterizerState() { impl_->~Impl(); }

}  // namespace graphics
}  // namespace temp
