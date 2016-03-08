/**
 * @file opengl_mac.h
 * @brief opengl utility for mac
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-01
 */
#pragma once
#ifndef GUARD_9421abba898147c393b08f37b524790f
#define GUARD_9421abba898147c393b08f37b524790f
#include "temp/define.h"

#ifdef TEMP_PLATFORM_MAC

#include "temp/graphics/opengl/opengl_common.h"
#include "temp/type.h"

namespace temp {
namespace graphics {
namespace opengl {
namespace mac {

using NsWindow = void*;
using NsOpenglContext = void*;

OpenglContexts createContexts(NsWindow window, Size worker_thread_count);
void deleteContexts(const OpenglContexts &contexts);

void makeCurrent(NsWindow window, NsOpenglContext context);

} // namespace mac
} // namespace opengl
} // namespace graphics
} // namespace temp

#endif
#endif // GUARD_9421abba898147c393b08f37b524790f
