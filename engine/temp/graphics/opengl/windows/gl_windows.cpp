#include "temp/graphics/opengl/windows/gl_windows.h"
#if defined(TEMP_PLATFORM_WINDOWS) && defined(TEMP_GRAPHICS_OPENGL)
#include "temp/core/core.h"

#include <Windows.h>

#include <mutex>

namespace temp {
namespace graphics {
namespace opengl {
namespace windows {

namespace {
const Char* kGlWindows = "GlWindows";

// ダミーウィンドウ作成
HWND CreateDummyWindow() {
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

  return CreateWindow(window_class_name, "", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                      0, CW_USEDEFAULT, 0, NULL, NULL, instance_handle, NULL);
}

// ダミーコンテキスト作成
HGLRC CreateDummyOpenglContext(HDC hdc) {
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
void InitializeOpenglExtension() {
#define TEMP_OPENGL_EXTENSION_LINK(func, name)                      \
  if (name == nullptr) *(void**)(&name) = wglGetProcAddress(#name); \
// if(name == nullptr) temp::system::Logger::info("OpenGL extention : {0}
// not supported.", #name);
#include "temp/graphics/opengl/gl_ext/temp_glext_link.inl"
#include "temp/graphics/opengl/gl_ext/temp_wglext_link.inl"
#undef TEMP_OPENGL_EXTENSION_LINK
}

OpenGLContextHandle CreateContextImpl(HDC hdc,
                                      OpenGLContextHandle shared_context) {
  // OpeGL拡張機能初期化用のダミーウィンドウとコンテキストを作成
  auto dummy_window_handle = CreateDummyWindow();
  auto dummy_device_context = GetDC(dummy_window_handle);
  auto dummy_opengl_context = CreateDummyOpenglContext(dummy_device_context);
  BOOL result = wglMakeCurrent(dummy_device_context, dummy_opengl_context);

  GLenum error;
  InitializeOpenglExtension();

  // OpenGL情報取得
  auto vendor = glGetString(GL_VENDOR);
  if (vendor != nullptr) {
    StringStream msg;
    msg << "vendor : " << vendor;
    TEMP_LOG_INFO(kGlWindows, msg.str());
  }
  auto render = glGetString(GL_RENDER);
  if (render != nullptr) {
    StringStream msg;
    msg << "render : " << render;
    TEMP_LOG_INFO(kGlWindows, msg.str());
  }
  auto version = glGetString(GL_VERSION);
  if (version != nullptr) {
    StringStream msg;
    msg << "version : " << version;
    TEMP_LOG_INFO(kGlWindows, msg.str());
  }
  auto extensions = glGetString(GL_EXTENSIONS);
  if (extensions != nullptr) {
    String extensionsStr = reinterpret_cast<const Char*>(extensions);
    // std::replace(extensionsStr.begin(), extensionsStr.end(), ' ', '\n');
    StringStream msg;
    msg << "extensions : " << extensionsStr;
    TEMP_LOG_INFO(kGlWindows, msg.str());
  }
  String version_string = reinterpret_cast<const char*>(version);
  StringStream ss(version_string);
  Vector<String> num_strs;
  String temp;
  while (std::getline(ss, temp, '.')) {
    num_strs.push_back(temp);
  }
  int major_version = std::stoi(num_strs[0].c_str());
  int minor_version = std::stoi(num_strs[1].c_str());

  // 拡張機能によるコンテキストの作成
  const FLOAT attrib_list[] = {0, 0};

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
  int context_attrib_list[] = {
    WGL_CONTEXT_MAJOR_VERSION_ARB,
    major_version,  //
    WGL_CONTEXT_MINOR_VERSION_ARB,
    minor_version,  //
#if _DEBUG
    WGL_CONTEXT_FLAGS_ARB,
    WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
    WGL_CONTEXT_PROFILE_MASK_ARB,
    WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0,
    0,  // End
  };

  int pixel_format = 0;
  UINT num_formats = 0;

  // ピクセルフォーマット選択
  BOOL is_valid =
      wglChoosePixelFormatARB(hdc, pixel_format_attrib_list, attrib_list, 1,
                              &pixel_format, &num_formats);

  error = glGetError();
  if (is_valid == FALSE) {
    TEMP_ASSERT(false, "");
  }

  // ピクセルフォーマット設定
  PIXELFORMATDESCRIPTOR pfd;
  DescribePixelFormat(hdc, pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
  result = SetPixelFormat(hdc, pixel_format, &pfd);
  if (result == FALSE) {
    TEMP_ASSERT(false, "");
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
    TEMP_ASSERT(false, "");
  }

  // ダミーのコンテキストとウィンドウを削除
  result = wglDeleteContext(dummy_opengl_context);
  if (result == FALSE) {
    TEMP_ASSERT(false, "");
  }

  result = ReleaseDC(dummy_window_handle, dummy_device_context);
  if (result == FALSE) {
    TEMP_ASSERT(false, "");
  }

  result = DestroyWindow(dummy_window_handle);
  if (result == FALSE) {
    TEMP_ASSERT(false, "");
  }

  if (shared_context != nullptr) {
    result = wglShareLists(context, shared_context);
    if (result == FALSE) {
      auto err = GetLastError();
      StringStream msg;
      msg << "wglShareLists failed. " << err;
      TEMP_LOG_FATAL(kGlWindows, msg.str());
    }
  }

#ifdef _DEBUG
  result = wglMakeCurrent(hdc, context);
  if (result == FALSE) {
    TEMP_ASSERT(false, "");
  }
  glDebugMessageCallback(DebugProc, nullptr);
  // カレントコンテキストを解除
  result = wglMakeCurrent((HDC)NULL, (HGLRC)NULL);
  if (result == FALSE) {
    TEMP_ASSERT(false, "");
  }
#endif

  return context;
}
}  // namespace

OpenGLContextHandle CreateContext(const void* window,
                                  OpenGLContextHandle shared_context) {
  HDC hdc = GetDC((HWND)window);
  return CreateContextImpl(hdc, shared_context);
}

void DeleteContext(OpenGLContextHandle context) { wglDeleteContext(context); }

void MakeCurrent(const void* window, OpenGLContextHandle context) {
  (void)context;
  auto hdc = GetDC((HWND)window);
  wglMakeCurrent(hdc, context);
}

void SwapBuffers(OpenGLContextHandle context) {
  (void)context;
  auto hdc = wglGetCurrentDC();
  SwapBuffers(hdc);
}

OpenGLContextHandle CreateSharedContext(OpenGLContextHandle shared_context) {
  auto current_context = wglGetCurrentContext();
  auto hdc = wglGetCurrentDC();
  auto context = CreateContextImpl(hdc, shared_context);
  wglMakeCurrent(hdc, current_context);
  return context;
}
}  // namespace windows
}  // namespace opengl
}  // namespace graphics
}  // namespace temp

#endif