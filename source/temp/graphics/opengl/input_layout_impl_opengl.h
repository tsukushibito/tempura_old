/**
 * @file input_layout_impl_opengl.h
 * @brief OpenGL input layout
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-05-09
 */
#pragma once
#ifndef GUARD_8ece5378020744c7a2c3d3836035c529
#define GUARD_8ece5378020744c7a2c3d3836035c529
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/type.h"
#include "temp/graphics/input_layout.h"

#include "temp/graphics/opengl/opengl_common.h"

namespace temp {
namespace graphics {

class InputLayout::Impl {
    friend class InputLayout;

public:
    Impl(NativeHandle device, InputLayout &input_layout, const InputElementDesc element_descs[], UInt32 element_count);
    ~Impl();

    Impl &operator=(const Impl &) = delete;

private:
    InputLayout &input_layout_;
    Vector<InputElementDesc> element_descs_;
};

} // namespace graphics
} // namespace temp

#endif

#endif // GUARD_8ece5378020744c7a2c3d3836035c529
