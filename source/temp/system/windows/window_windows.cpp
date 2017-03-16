#include "temp/define.h"
#ifdef TEMP_PLATFORM_WINDOWS
#include <Windows.h>

#include "temp/system/window.h"

namespace temp {
namespace system {

namespace {
LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY: /* 終了処理 */

        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}
}

class Window::Impl {
public:
    Impl(Size width, Size height) {
        WNDCLASSEX wndclass;
        HINSTANCE  hInstance = GetModuleHandle(NULL);

        wndclass.cbSize      = sizeof(wndclass); /* 構造体の大きさ */
        wndclass.style       = CS_HREDRAW | CS_VREDRAW; /* スタイル */
        wndclass.lpfnWndProc = wndProc; /* メッセージ処理関数 */
        wndclass.cbClsExtra  = 0;
        wndclass.cbWndExtra  = 0;
        wndclass.hInstance   = hInstance; /* プログラムのハンドル */
        wndclass.hIcon   = LoadIcon(NULL, IDI_APPLICATION); /* アイコン */
        wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);     /* カーソル */
        wndclass.hbrBackground
            = (HBRUSH)GetStockObject(WHITE_BRUSH); /* ブラシ */
        wndclass.lpszMenuName  = NULL;             /* メニュー */
        wndclass.lpszClassName = "TempuraWindow";  /* クラス名 */
        wndclass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

        RegisterClassEx(&wndclass); /* ウインドウクラスTest Windowを登録 */

        // クライアント領域を指定サイズにするため調整
        DWORD style       = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
        RECT  window_rect = {
            0, 0, static_cast<LONG>(width), static_cast<LONG>(height),
        };
        AdjustWindowRect(&window_rect, style, FALSE);
        LONG window_width  = window_rect.right - window_rect.left;
        LONG window_height = window_rect.bottom - window_rect.top;
        hWnd_              = CreateWindow(
            "TempuraWindow",              /* ウインドウクラス名 */
            "てんぷら",                   /* ウインドウのタイトル */
            style,                        /* ウインドウスタイル */
            CW_USEDEFAULT, CW_USEDEFAULT, /* ウインドウ表示位置 */
            window_width, window_height,  /* ウインドウの大きさ */
            NULL,      /* 親ウインドウのハンドル */
            NULL,      /* メニューのハンドル */
            hInstance, /* インスタンスのハンドル */
            NULL);     /* 作成時の引数保存用ポインタ */

        ShowWindow(hWnd_, SW_SHOW); /* ウインドウを表示 */
        UpdateWindow(hWnd_);
    }

    ~Impl() {
        // DestroyWindow(hWnd_);
    }

    WindowHandle windowHandle() const {
		return WindowHandle(0);
    }

private:
    HWND hWnd_;
};

Window::Window(Size width, Size height)
    : impl_(new Impl(width, height)), width_(width), height_(height) {}

Window::~Window() {}


Window::SPtr Window::create(Size width, Size height) {
    struct Creator : public Window {
        Creator(Size width, Size height) : Window(width, height) {}
    };

    auto p = std::make_shared<Creator>(width, height);
    return std::move(p);
}
}
}
#endif  // TEMP_PLATFORM_WINDOWS
