#include "temp/graphics_old/opengl/windows/opengl_windows.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include <iostream>
#include <sstream>

namespace {

// ダミーウィンドウ作成
HWND createDummyWindow() {
    const size_t kMaxStrSize = 100;
    HINSTANCE instance_handle = GetModuleHandle(NULL);
    CHAR window_class_name[kMaxStrSize] = "Dummy";
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = DefWindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = instance_handle;
    wcex.hIcon = NULL;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = window_class_name;
    wcex.hIconSm = NULL;

    RegisterClassEx(&wcex);

    return CreateWindow(window_class_name, "", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL,
                        instance_handle, NULL);
}

// ダミーコンテキスト作成
HGLRC createDummyOpenglContext(HDC hdc) {
    // 現在対応しているフォーマットの数を参照する
    // int format_count= DescribePixelFormat( hTempDC, 0, 0, NULL );

    PIXELFORMATDESCRIPTOR pfd;
    // 列挙する
    // for (int i = 0; i < format_count; ++i) {
    //     DescribePixelFormat(hTempDC, i + 1, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
    //     break;
    // }
    DescribePixelFormat(hdc, 1, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

    // ピクセルフォーマットの選択
    int pfmt = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, pfmt, &pfd);

    // OpenGL コンテキストの作成
    return wglCreateContext(hdc);
}

void initializeOpenglExtension() {
#define TEMP_OPENGL_EXTENSION_LINK(func, name) \
	if(name == nullptr) *(void**)(&name) = wglGetProcAddress(#name);	\
	// if(name == nullptr) temp::system::Logger::info("OpenGL extention : {0} not supported.", #name);
#include <gl_ext/temp_glext_link.inl>
#include <gl_ext/temp_wglext_link.inl>
#undef TEMP_OPENGL_EXTENSION_LINK
}

} // namespace

namespace temp {
namespace graphics_old {
namespace opengl {
namespace windows {

OpenglContexts createContexts(HWND window_handle, Size worker_thread_count) {
	using temp::system::Logger;

    // OpeGL拡張機能初期化用のダミーウィンドウとコンテキストを作成
    auto dummy_window_handle = createDummyWindow();
    auto dummy_device_context = GetDC(dummy_window_handle);
    auto dummy_opengl_context = createDummyOpenglContext(dummy_device_context);
    BOOL result = wglMakeCurrent(dummy_device_context, dummy_opengl_context);

	GLenum error;
#ifdef TEMP_USE_GLEW
	// glewの初期化
	error = glewInit();
	if (error != GLEW_OK)
	{
		Logger::error("glewInit failed!: {0}", glewGetErrorString(error));
	}
	else
	{
		Logger::info("glewInit version: {0}", glewGetString(GLEW_VERSION));
	}
#else
	initializeOpenglExtension();
#endif
	// OpenGL情報取得
	auto vendor = glGetString(GL_VENDOR);
	if (vendor != nullptr) Logger::info("[OpenGL] vendor : {0}", vendor);
	// auto renderer = glGetString(GL_RENDER);
	// if (renderer != nullptr) Logger::info("[OpenGL] renderer : {0}", renderer);
	auto version = glGetString(GL_VERSION);
	if (version != nullptr) Logger::info("[OpenGL] version : {0}", version);
	// auto extensions = glGetString(GL_EXTENSIONS);
	// if ( extensions != nullptr) Logger::info("[OpenGL] extensions : {0}", extensions);
	String version_string = reinterpret_cast<const char*>(version);
	StringStream ss(version_string);
	Vector<String> num_strs;
	String temp;
	while (std::getline(ss, temp, '.')) {
		num_strs.push_back(temp);
	}
	int majorVersion = std::stoi(num_strs[0]);
	int minorVersion = std::stoi(num_strs[1]);


    // 拡張機能によるコンテキストの作成
    const FLOAT fAtribList[] = { 0, 0 };

    // ピクセルフォーマット指定用
    const int pixel_format_attrib_list[] = {
        // WGL_CONTEXT_MAJOR_VERSION_ARB, 1,
        // WGL_CONTEXT_MINOR_VERSION_ARB, 0,
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE, //
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE, //
        WGL_DOUBLE_BUFFER_ARB,  GL_TRUE, //
        // WGL_DOUBLE_BUFFER_ARB, GL_FALSE, //
        WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB, //
        WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,         //
        WGL_COLOR_BITS_ARB,     32,                        //
        WGL_DEPTH_BITS_ARB,     24,                        //
        WGL_STENCIL_BITS_ARB,   8,                         //
        0,                      0,                         //
    };

    // コンテキスト作成用
    int context_attrib_list[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB,
        majorVersion, //
        WGL_CONTEXT_MINOR_VERSION_ARB,
        minorVersion, //
#if DEBUG
        WGL_CONTEXT_FLAGS_ARB,
        WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
        WGL_CONTEXT_PROFILE_MASK_ARB,
        WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0,
        0, // End
    };

    int pixelFormat = 0;
    UINT numFormats = 0;
    HDC hdc = GetDC(window_handle);

    // ピクセルフォーマット選択
    BOOL isValid = wglChoosePixelFormatARB(hdc, pixel_format_attrib_list, fAtribList, 1, &pixelFormat, &numFormats);

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

    // コンテキスト作成
    OpenglContexts output;

    // 描画スレッド用
    output.context_for_render_thread = wglCreateContextAttribsARB(hdc, NULL, context_attrib_list);
    while (output.context_for_render_thread == NULL) {
        // 成功するまでバージョンを下げる
        context_attrib_list[3] -= 1;
        if (context_attrib_list[3] < 0) {
            context_attrib_list[3] = 10;
            context_attrib_list[1] -= 1;
            if (context_attrib_list[1] < 0) {
                break;
            }
        }
        output.context_for_render_thread = wglCreateContextAttribsARB(hdc, NULL, context_attrib_list);
    }

    // applicationスレッド用
    output.context_for_application_thread = wglCreateContextAttribsARB(hdc, NULL, context_attrib_list);
    wglShareLists((HGLRC)output.context_for_render_thread, (HGLRC)output.context_for_application_thread);

    // メインスレッド用
    output.context_for_main_thread = wglCreateContextAttribsARB(hdc, NULL, context_attrib_list);
    wglShareLists((HGLRC)output.context_for_render_thread, (HGLRC)output.context_for_main_thread);

    // ロードスレッド用
    output.context_for_load_thread = wglCreateContextAttribsARB(hdc, NULL, context_attrib_list);
    wglShareLists((HGLRC)output.context_for_render_thread, (HGLRC)output.context_for_load_thread);

	for (Size i = 0; i < worker_thread_count; ++i) {
        auto context = wglCreateContextAttribsARB(hdc, NULL, context_attrib_list);
		output.contexts_for_worker_thread.push_back(context);
        wglShareLists((HGLRC)output.context_for_render_thread, context);
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

    return output;
}

void deleteContexts(const OpenglContexts &contexts) {
	glCallWithErrorCheck(wglDeleteContext, static_cast<HGLRC>(contexts.context_for_main_thread));
	glCallWithErrorCheck(wglDeleteContext, static_cast<HGLRC>(contexts.context_for_render_thread));
	glCallWithErrorCheck(wglDeleteContext, static_cast<HGLRC>(contexts.context_for_load_thread));
	for (auto &&context : contexts.contexts_for_worker_thread)
	{
		glCallWithErrorCheck(wglDeleteContext, static_cast<HGLRC>(context));
	}
}

void makeCurrent(HWND window_handle, HGLRC context) {
	HDC hdc = GetDC(window_handle);
	wglMakeCurrent(hdc, context);
	ReleaseDC(window_handle, hdc);
}

void swapBuffers(HWND window_handle, HGLRC context) {
	(void*)context;
	HDC hdc = GetDC(window_handle);
	wglSwapLayerBuffers(hdc, WGL_SWAP_MAIN_PLANE);
	ReleaseDC(window_handle, hdc);
}

} // namespace windows
} // namespace opengl
} // namespace graphics
} // namespace

#endif // TEMP_PLATFORM_WINDOWS
