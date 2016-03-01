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

struct OpenglContexts {
    HGLRC context_for_render;
    HGLRC context_for_load;
};

/**
 * @brief OpenGL デバッグプロシージャ
 *
 * @param source
 * @param type
 * @param id
 * @param severity
 * @param length
 * @param message
 * @param user_param
 *
 * @return
 */
void GLAPIENTRY debugProc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                           const GLchar *message, const void *user_param);


/**
 * @brief GLEWを使用してOpenGLコンテキストを作成
 *
 * @param hdc デバイスコンテキスト
 *
 * @return OpenGLコンテキスト（描画用とロード用の二つ）
 */
OpenglContexts createContextWithGLEW(HDC hdc);

} // namespace windows
} // namespace opengl
} // namespace graphics
} // namespace temp

#endif // TEMP_PLATFORM_WINDOWS
#endif // GUARD_6a2942d950e146d096151e9911d4f47e
