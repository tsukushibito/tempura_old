/**
 * @file graphics.h
 * @brief
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-02-27
 */
#pragma once
#ifndef GUARD_06ee30f321684357842780bfa43ecbf1
#define GUARD_06ee30f321684357842780bfa43ecbf1

#include "temp/define.h"
#include "temp/type.h"

#include "temp/graphics/graphics_common.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics/opengl/opengl_device.h"
#include "temp/graphics/opengl/opengl_texture.h"
#endif

namespace temp {
namespace graphics {}
}

#endif  // GUARD_06ee30f321684357842780bfa43ecbf1
