#include "temp/graphics/opengl/windows/opengl_windows.h"

#if defined(TEMP_PLATFORM_WINDOWS)

#include <iostream>
#include <mutex>

#include "temp/container.h"
#include "temp/system/logger.h"

namespace temp {
namespace graphics {
namespace opengl {
namespace windows {

namespace {
// ハンドル管理テーブル
temp::Vector<HGLRC> g_handle_table;
std::mutex          g_handle_table_mutex;

DeviceHandle pushHGLRCToTable(HGLRC context) {
    std::lock_guard<std::mutex> lock(g_handle_table_mutex);
    for (Int32 i = 0; i < g_handle_table.size(); ++i) {
        if (g_handle_table[i] == context) {
            std::cout << "HGLRC[0x" << std::hex << context
                      << "] already exists in table!" << std::endl;
            return DeviceHandle(i);
        } else if (g_handle_table[i] == nullptr) {
            return DeviceHandle(i);
        }
    }

    g_handle_table.push_back(context);
    return DeviceHandle(g_handle_table.size() - 1);
}

void removeNSOpenGLContextFromTable(HGLRC context) {
    std::lock_guard<std::mutex> lock(g_handle_table_mutex);
    for (Int32 i = 0; i < g_handle_table.size(); ++i) {
        if (g_handle_table[i] == context) {
            g_handle_table[i] = nullptr;
            return;
        }
    }
    std::cout << "HGLRC[0x" << std::hex << context << "] is not found in table!"
              << std::endl;
}

HGLRC deviceHandleToHGLRC(const DeviceHandle& handle) {
    std::lock_guard<std::mutex> lock(g_handle_table_mutex);
    return nullptr;
}


// ダミーウィンドウ作成
HWND createDummyWindow() {
    const size_t kMaxStrSize                    = 100;
    HINSTANCE    instance_handle                = GetModuleHandle(NULL);
    CHAR         window_class_name[kMaxStrSize] = "Dummy";
    WNDCLASSEX   wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style         = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc   = DefWindowProc;
    wcex.cbClsExtra    = 0;
    wcex.cbWndExtra    = 0;
    wcex.hInstance     = instance_handle;
    wcex.hIcon         = NULL;
    wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName  = NULL;
    wcex.lpszClassName = window_class_name;
    wcex.hIconSm       = NULL;

    RegisterClassEx(&wcex);

    return CreateWindow(window_class_name, "", WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL,
                        instance_handle, NULL);
}

// ダミーコンテキスト作成
HGLRC createDummyOpenglContext(HDC hdc) {
    // 現在対応しているフォーマットの数を参照する
    // int format_count= DescribePixelFormat( hTempDC, 0, 0, NULL );

    PIXELFORMATDESCRIPTOR pfd;
    // 列挙する
    // for (int i = 0; i < format_count; ++i) {
    //     DescribePixelFormat(hTempDC, i + 1, sizeof(PIXELFORMATDESCRIPTOR),
    //     &pfd);
    //     break;
    // }
    DescribePixelFormat(hdc, 1, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    // ピクセルフォーマットの選択
    int pfmt = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pfmt, &pfd);

    // OpenGL コンテキストの作成
    return wglCreateContext(hdc);
}

// OpenGL拡張の初期化
void initializeOpenglExtension() {
#define TEMP_OPENGL_EXTENSION_LINK(func, name)                        \
    if (name == nullptr) *(void**)(&name) = wglGetProcAddress(#name); \
// if(name == nullptr) temp::system::ConsoleLogger::info("OpenGL extention : {0}
// not supported.", #name);
#include <gl_ext/temp_glext_link.inl>
#include <gl_ext/temp_wglext_link.inl>
#undef TEMP_OPENGL_EXTENSION_LINK
}
}

DeviceHandle createContext(const temp::system::WindowHandle& window_handle) {
    // OpeGL拡張機能初期化用のダミーウィンドウとコンテキストを作成
    auto dummy_window_handle  = createDummyWindow();
    auto dummy_device_context = GetDC(dummy_window_handle);
    auto dummy_opengl_context = createDummyOpenglContext(dummy_device_context);
    BOOL result = wglMakeCurrent(dummy_device_context, dummy_opengl_context);

    GLenum error;
#ifdef TEMP_USE_GLEW
    // glewの初期化
    error = glewInit();
    if (error != GLEW_OK) {
        ConsoleLogger::error("glewInit failed!: {0}",
                             glewGetErrorString(error));
    } else {
        ConsoleLogger::info("glewInit version: {0}",
                            glewGetString(GLEW_VERSION));
    }
#else
    initializeOpenglExtension();
#endif
    // OpenGL情報取得
    using temp::system::ConsoleLogger;
    auto vendor = glGetString(GL_VENDOR);
    if (vendor != nullptr) ConsoleLogger::info("[OpenGL] vendor : {0}", vendor);
    auto renderer = glGetString(GL_RENDER);
    if (renderer != nullptr)
        ConsoleLogger::info("[OpenGL] renderer : {0}", renderer);
    auto version = glGetString(GL_VERSION);
    if (version != nullptr)
        ConsoleLogger::info("[OpenGL] version : {0}", version);
    auto extensions = glGetString(GL_EXTENSIONS);
    if (extensions != nullptr)
        ConsoleLogger::info("[OpenGL] extensions : {0}", extensions);
    String         version_string = reinterpret_cast<const char*>(version);
    StringStream   ss(version_string);
    Vector<String> num_strs;
    String         temp;
    while (std::getline(ss, temp, '.')) {
        num_strs.push_back(temp);
    }
    int majorVersion = std::stoi(num_strs[0]);
    int minorVersion = std::stoi(num_strs[1]);


    // 拡張機能によるコンテキストの作成
    const FLOAT fAtribList[] = {0, 0};

    // ピクセルフォーマット指定用
    const int pixel_format_attrib_list[] = {
        // WGL_CONTEXT_MAJOR_VERSION_ARB, 1,
        // WGL_CONTEXT_MINOR_VERSION_ARB, 0,
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,  //
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,  //
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,   //
        // WGL_DOUBLE_BUFFER_ARB, GL_FALSE, //
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,  //
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,            //
        WGL_COLOR_BITS_ARB, 32,                           //
        WGL_DEPTH_BITS_ARB, 24,                           //
        WGL_STENCIL_BITS_ARB, 8,                          //
        0, 0,                                             //
    };

    // コンテキスト作成用
    int context_attrib_list[]
        = { WGL_CONTEXT_MAJOR_VERSION_ARB,
            majorVersion,  //
            WGL_CONTEXT_MINOR_VERSION_ARB,
            minorVersion,  //
#if DEBUG
            WGL_CONTEXT_FLAGS_ARB,
            WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
            WGL_CONTEXT_PROFILE_MASK_ARB,
            WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0,
            0,  // End
          };

    int  pixelFormat = 0;
    UINT numFormats  = 0;
    HDC  hdc         = GetDC(window_handle);

    // ピクセルフォーマット選択
    BOOL isValid
        = wglChoosePixelFormatARB(hdc, pixel_format_attrib_list, fAtribList, 1,
                                  &pixelFormat, &numFormats);

    error = glGetError();
    if (isValid == FALSE) {
        assert(false);
    }

    // ピクセルフォーマット設定
    PIXELFORMATDESCRIPTOR pfd;
    DescribePixelFormat(hdc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    result = SetPixelFormat(hdc, pixelFormat, &pfd);
    if (result == FALSE) {
        assert(false);
    }

    auto context = wglCreateContextAttribsARB(hdc, NULL, context_attrib_list);
    while (context == NULL) {
        // 成功するまでバージョンを下げる
        context_attrib_list[3] -= 1;
        if (context_attrib_list[3] < 0) {
            context_attrib_list[3] = 10;
            context_attrib_list[1] -= 1;
            if (context_attrib_list[1] < 0) {
                break;
            }
        }
        context = wglCreateContextAttribsARB(hdc, NULL, context_attrib_list);
    }

    // カレントコンテキストを解除
    result = wglMakeCurrent((HDC)NULL, (HGLRC)NULL);
    if (result == FALSE) {
        assert(false);
    }

    // ダミーのコンテキストとウィンドウを削除
    result = wglDeleteContext(dummy_opengl_context);
    if (result == FALSE) {
        assert(false);
    }

    result = ReleaseDC(dummy_window_handle, dummy_device_context);
    if (result == FALSE) {
        assert(false);
    }

    result = DestroyWindow(dummy_window_handle);
    if (result == FALSE) {
        assert(false);
    }

    auto deviceHandle = pushHGLRCToTable(context);

    return deviceHandle;
}

void deleteContext(HGLRC context) {}

void makeCurrent(HGLRC context) {}

void swapBuffers(HGLRC context) {}

void* deviceHandleToNsOpenGlContext(const DeviceHandle& handle) {}
}
}
}
}

#endif
