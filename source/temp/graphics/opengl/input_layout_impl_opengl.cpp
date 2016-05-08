/**
 * @file input_layout_impl_opengl.cpp
 * @brief OpenGL input layout
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-05-09
 */

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/input_layout.h"

#include "temp/graphics/opengl/opengl_common.h"
#include "temp/graphics/opengl/input_layout_impl_opengl.h"

namespace temp {
namespace graphics {

InputLayout::Impl::Impl(NativeHandle device, InputLayout &input_layout, const InputElementDesc element_descs[],
                        UInt32 element_count)
    : input_layout_(input_layout) {
}

} // namespace graphics
} // namespace temp
#endif // TEMP_GRAPHICS_OPENGL