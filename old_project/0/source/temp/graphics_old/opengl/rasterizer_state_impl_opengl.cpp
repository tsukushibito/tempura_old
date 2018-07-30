/**
 * @file rasterizer_state_impl_opengl.cpp
 * @brief OpenGL Rasterizer State
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-24
 */
#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/rasterizer_state.h"
#include "temp/type.h"

#include "temp/graphics_old/opengl/opengl_common.h"
#include "temp/graphics_old/opengl/rasterizer_state_impl_opengl.h"

namespace temp {
namespace graphics_old {

RasterizerState::Impl::Impl(NativeHandle     device,
                            RasterizerState& rasterizer_state,
                            RasterizerDesc   desc)
    : rasterizer_state_(rasterizer_state) {
    switch (desc.cull_mode) {
    case CullingMode::CullingNone:
        arg_.culling_mode = GL_FRONT;
        break;
    case CullingMode::CullingFront:
        arg_.culling_mode = GL_FRONT;
        break;
    case CullingMode::CullingBack:
        arg_.culling_mode = GL_BACK;
        break;
    }

    switch (desc.front_face) {
    case FrontFace::ClockWise:
        arg_.front_face = GL_CW;
        break;
    case FrontFace::CounterClockWise:
        arg_.front_face = GL_CCW;
        break;
    }

    switch (desc.fill_mode) {
    case FillMode::Line:
        arg_.polygon_mode = GL_LINE;
        break;
    case FillMode::Fill:
        arg_.polygon_mode = GL_FILL;
        break;
    }


    rasterizer_state_.native_handle_.pointer = &arg_;
    temp::system::Logger::trace("OpenGL Rasterizer State has created!");

    (void)device;
}

RasterizerState::Impl::~Impl() {
    using namespace opengl;
    temp::system::Logger::trace("OpenGL Rasterizer State has deleted!");
}

}  // namespace graphics
}  // namespace temp
#endif
