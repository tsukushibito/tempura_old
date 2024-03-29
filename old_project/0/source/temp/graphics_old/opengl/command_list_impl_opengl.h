/**
 * @file command_list_impl_opengl.h
 * @brief OpenGL command list
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-04-06
 */
#pragma once
#ifndef GUARD_f4973063f6ed491f9b29014643b9b2ef
#define GUARD_f4973063f6ed491f9b29014643b9b2ef

#include "temp/define.h"
#ifdef TEMP_GRAPHICS_OPENGL
#include "temp/graphics_old/command_list.h"
#include "temp/type.h"

#include "temp/graphics_old/opengl/opengl_common.h"

namespace temp {
namespace graphics_old {

class CommandList::Impl {
    friend class CommandList;

private:
    Impl(CommandList& command_list);
    ~Impl();
    Impl& operator=(const Impl&) = delete;

    CommandList& command_list_;
};
}
}

#endif  // TEMP_GRAPHICS_OPENGL
#endif  // GUARD_f4973063f6ed491f9b29014643b9b2ef
