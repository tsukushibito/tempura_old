/**
 * @file define.h
 * @brief preprocess defines
 * @author tsukushibito
 * @version 0.0.1
 * @date 2016-02-21
 */
#pragma once
#ifndef GUARD_a872673f15ff4a4797eef84914288e90
#define GUARD_a872673f15ff4a4797eef84914288e90

#if defined(__alpha__) || defined(__ia64__) || defined(__x86_64__) || \
    defined(_WIN64) || defined(__LP64__) || defined(__LLP64__)
#define TEMP_64BIT
#endif

#if defined _WIN32
#define TEMP_PLATFORM_WINDOWS
#elif defined __APPLE__
#define TEMP_PLATFORM_MAC
#elif defined __gnu_linux__
#define TEMP_PLATFORM_LINUX
#elif defined __ANDROID__
#define TEMP_PLATFORM_ANDROID
#endif

// #define TEMP_USE_D3D11
#ifdef TEMP_USE_D3D11
#define TEMP_GRAPHICS_D3D11
#else
#define TEMP_GRAPHICS_OPENGL
// #define TEMP_OPENGL_WITHOUT_CHECK_ERROR
#endif

#endif  // GUARD_a872673f15ff4a4797eef84914288e90
