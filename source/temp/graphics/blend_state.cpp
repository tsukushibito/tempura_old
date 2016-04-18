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
#endif

namespace temp {
namespace graphics {

class BlendState::Impl {
};

BlendState::SPtr BlendState::create(NativeHandle device) {
    struct Creator : public BlendState {
        Creator(NativeHandle device) : BlendState(device) {}
    };
    auto p = std::make_shared< Creator >(device);
    return std::move(p);
}

BlendState::BlendState(NativeHandle device) {
    static_assert(sizeof(Impl) <= sizeof(impl_buffer_), "size of impl_buffer_ is small.");
    // impl_ = new (impl_buffer_) Impl(*this, source, is_binary);

    (void)&device; // 未使用引数
}

BlendState::~BlendState() { impl_->~Impl(); }
    
} // namespace graphics
} // namespace temp
