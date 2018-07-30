/**
 * @file input_layout.cpp
 * @brief input layout
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-05-08
 */

#include <new>

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics_old/input_layout.h"
#if defined   TEMP_GRAPHICS_D3D11
#elif defined TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/opengl/input_layout_impl_opengl.h"
#endif

namespace temp {
namespace graphics_old {

InputLayout::SPtr InputLayout::create(NativeHandle           device,
                                      const InputElementDesc element_descs[],
                                      UInt32                 element_count) {
    struct Creator : public InputLayout {
        Creator(NativeHandle device, const InputElementDesc element_descs[],
                UInt32 element_count)
            : InputLayout(device, element_descs, element_count) {}
    };
    auto p = std::make_shared<Creator>(device, element_descs, element_count);
    return std::move(p);
}

InputLayout::InputLayout(NativeHandle           device,
                         const InputElementDesc element_descs[],
                         UInt32                 element_count) {
    static_assert(sizeof(Impl) <= sizeof(impl_buffer_),
                  "size of impl_buffer_ is small.");
    impl_
        = new (impl_buffer_) Impl(device, *this, element_descs, element_count);
}

InputLayout::~InputLayout() { impl_->~Impl(); }

}  // namespace graphics
}  // namespace temp
