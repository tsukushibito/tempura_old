#pragma once

#if defined(__alpha__) || defined(__ia64__) || defined(__x86_64__) || \
    defined(_WIN64) || defined(__LP64__) || defined(__LLP64__)
#define TEMP_64BIT
#endif

#if defined _WIN32
#define TEMP_PLATFORM_WINDOWS
#ifdef TEMP_EXPORT
#define TEMP_DECLSPEC __declspec(dllexport)
#else
#define TEMP_DECLSPEC __declspec(dllimport)
#endif
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