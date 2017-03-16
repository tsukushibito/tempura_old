/**
 * @file define_opengl.h
 * @brief OpenGL 定義
 * @author tsukushibito
 * @version 0.0.1
 * @date 2017-03-01
 */
#pragma once
#ifndef GUARD_898e50a45d9d46a08367e75b738422ff
#define GUARD_898e50a45d9d46a08367e75b738422ff

#include "temp/define.h"

#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>
#endif

#if defined(TEMP_PLATFORM_WINDOWS) || defined(TEMP_PLATFORM_LINUX)

#include <GL/gl.h>
#include <GL/glu.h>
#include <gl_ext/glext.h>

#define TEMP_OPENGL_EXTENSION_LINK(func, name) extern func name;
#include <gl_ext/temp_glext_link.inl>

#if defined(TEMP_PLATFORM_LINUX)
#include <gl_ext/glxext.h>

#elif defined(TEMP_PLATFORM_WINDOWS)
#include <gl_ext/wglext.h>
#include <gl_ext/temp_wglext_link.inl>
#endif
#undef TEMP_OPENGL_EXTENSION_LINK

#else

#include <OpenGL/OpenGL.h>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#endif  // defined(TEMP_PLATFORM_WINDOWS) || defined(TEMP_PLATFORM_LINUX)

#endif  // GUARD_898e50a45d9d46a08367e75b738422ff
