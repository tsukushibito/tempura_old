#include "temp/system/windows/windows_application.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>

#include "temp/core/logger.h"

namespace temp {
namespace system {
namespace windows {

namespace {
const char *kWinAppTag = "WindowsApplication";
LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_DESTROY:

      PostQuitMessage(0);
      return 0;
  }

  return DefWindowProc(hWnd, msg, wParam, lParam);
}
}  // namespace

WindowsApplication::WindowsApplication() {
  TEMP_LOG_TRACE(kWinAppTag, "created");
}

WindowsApplication::~WindowsApplication() {
  TEMP_LOG_TRACE(kWinAppTag, "destroied");
}

Int32 WindowsApplication::Run() {
  Init();
  on_initialize_();

  MSG msg;
  {
    while (true) {
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
          break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      } else {
        on_update_();
      }
    }
  }

  on_terminate_();
  Term();

  return static_cast<Int32>(msg.wParam);
}

void WindowsApplication::Exit() {
  HWND hwnd = reinterpret_cast<HWND>(native_window_handle_);
  SendMessage(hwnd, WM_QUIT, 0, 0);
}

void WindowsApplication::Init() {
  TEMP_LOG_TRACE(kWinAppTag, "init");

  WNDCLASSEX wndclass;
  HINSTANCE instance_handle = GetModuleHandle(NULL);

  wndclass.cbSize = sizeof(wndclass);
  wndclass.style = CS_HREDRAW | CS_VREDRAW;
  wndclass.lpfnWndProc = wndProc;
  wndclass.cbClsExtra = 0;
  wndclass.cbWndExtra = 0;
  wndclass.hInstance = instance_handle;
  wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
  wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wndclass.lpszMenuName = NULL;
  wndclass.lpszClassName = "TempuraWindow";
  wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  RegisterClassEx(&wndclass);

  DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
  RECT window_rect = {
      0,
      0,
      static_cast<LONG>(1080),
      static_cast<LONG>(720),
  };
  AdjustWindowRect(&window_rect, style, FALSE);
  LONG window_width = window_rect.right - window_rect.left;
  LONG window_height = window_rect.bottom - window_rect.top;
  HWND hwnd = CreateWindow("TempuraWindow", "てんぷら", style, CW_USEDEFAULT,
                           CW_USEDEFAULT, window_width, window_height, NULL,
                           NULL, instance_handle, NULL);

  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);
  native_window_handle_ = hwnd;
}

void WindowsApplication::Term() {
  TEMP_LOG_TRACE(kWinAppTag, "term");
  HWND hwnd = reinterpret_cast<HWND>(native_window_handle_);
  DestroyWindow(hwnd);
}

}  // namespace windows
}  // namespace system
}  // namespace temp
#endif