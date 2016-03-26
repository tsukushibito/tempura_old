/**
 * @file opengl_windows.h
 * @brief OpenGL utility for Windows
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-03-01
 */
#pragma once
#ifndef GUARD_6a2942d950e146d096151e9911d4f47e
#define GUARD_6a2942d950e146d096151e9911d4f47e

#include "temp/define.h"

#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>

#include "temp/graphics/opengl/opengl_common.h"
#include "temp/type.h"

namespace temp {
namespace graphics {
namespace opengl {
namespace windows {

/**
 * @brief OpenGLコンテキストを作成
 *
 * @param window_handle Window handle
 *
 * @return OpenGLコンテキスト（各スレッド用に一つずつ）
 */
OpenglContexts createContexts(HWND window_handle, Size worker_thread_count);

void deleteContexts(const OpenglContexts &contexts);

void makeCurrent(HWND window_handle, HGLRC context);

void swapBuffers(HWND window_handle, HGLRC context);

} // namespace windows
} // namespace opengl
} // namespace graphics
} // namespace temp

#endif // TEMP_PLATFORM_WINDOWS
#endif // GUARD_6a2942d950e146d096151e9911d4f47e
