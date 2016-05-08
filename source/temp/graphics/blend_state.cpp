/**
 * @file blend_state.cpp
 * @brief blend state
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-19
 */

#include <new>

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics/blend_state.h"
#if defined TEMP_GRAPHICS_D3D11
#elif defined TEMP_GRAPHICS_OPENGL
#include "temp/graphics/opengl/blend_state_impl_opengl.h"
#endif

namespace temp {
namespace graphics {

BlendState::SPtr BlendState::create(NativeHandle device, BlendMode blend_mode) {
    struct Creator : public BlendState {
        Creator(NativeHandle device, BlendMode blend_mode) : BlendState(device, blend_mode) {}
    };
    auto p = std::make_shared< Creator >(device, blend_mode);
    return std::move(p);
}

BlendState::BlendState(NativeHandle device, BlendMode blend_mode) {
    static_assert(sizeof(Impl) <= sizeof(impl_buffer_), "size of impl_buffer_ is small.");
    impl_ = new (impl_buffer_) Impl(device, *this, blend_mode);
}

BlendState::~BlendState() { impl_->~Impl(); }

} // namespace graphics
} // namespace temp
