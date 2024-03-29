/**
 * @file input_layout_impl_opengl.cpp
 * @brief OpenGL input layout
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-05-09
 */

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/input_layout.h"
#include "temp/type.h"

#include "temp/graphics_old/opengl/input_layout_impl_opengl.h"
#include "temp/graphics_old/opengl/opengl_common.h"

namespace temp {
namespace graphics_old {

InputLayout::Impl::Impl(NativeHandle device, InputLayout& input_layout,
                        const InputElementDesc element_descs[],
                        UInt32                 element_count)
    : input_layout_(input_layout) {
    element_descs_.resize(element_count);
    memcpy(&element_descs_[0], element_descs,
           sizeof(InputElementDesc) * element_count);
    input_layout.native_handle_.pointer = &element_descs_;
}

}  // namespace graphics
}  // namespace temp
#endif  // TEMP_GRAPHICS_OPENGL
