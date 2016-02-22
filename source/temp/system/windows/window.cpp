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
        HINSTANCE hInstance = GetModuleHandle(NULL);

        wndclass.cbSize = sizeof(wndclass);       /* 構造体の大きさ */
        wndclass.style = CS_HREDRAW | CS_VREDRAW; /* スタイル */
        wndclass.lpfnWndProc = wndProc;           /* メッセージ処理関数 */
        wndclass.cbClsExtra = 0;
        wndclass.cbWndExtra = 0;
        wndclass.hInstance = hInstance;                               /* プログラムのハンドル */
        wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);             /* アイコン */
        wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);               /* カーソル */
        wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); /* ブラシ */
        wndclass.lpszMenuName = NULL;                                 /* メニュー */
        wndclass.lpszClassName = "TempuraWindow";                     /* クラス名 */
        wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        RegisterClassEx(&wndclass); /* ウインドウクラスTest Windowを登録 */

        hWnd_ = CreateWindow("TempuraWindow",                                       /* ウインドウクラス名 */
                             "てんぷら",                                            /* ウインドウのタイトル */
                             WS_OVERLAPPEDWINDOW,                                   /* ウインドウスタイル */
                             CW_USEDEFAULT, CW_USEDEFAULT,                          /* ウインドウ表示位置 */
                             static_cast< int >(width), static_cast< int >(height), /* ウインドウの大きさ */
                             NULL,                                                  /* 親ウインドウのハンドル */
                             NULL,                                                  /* メニューのハンドル */
                             hInstance,                                             /* インスタンスのハンドル */
                             NULL);                                                 /* 作成時の引数保存用ポインタ */

        ShowWindow(hWnd_, SW_SHOW); /* ウインドウを表示 */
        UpdateWindow(hWnd_);

        hDc_ = GetDC(hWnd_);
    }

    ~Impl() {
        // DestroyWindow(hWnd_);
        ReleaseDC(hWnd_, hDc_);
    }

    WindowHandle getWindowHandle() {
        WindowHandle handle;
        handle.pointer_ = hWnd_;
        return handle;
    }

    ViewHandle getViewHandle() {
        ViewHandle handle;
        handle.pointer_ = hDc_;
        return handle;
    }

private:
    HWND hWnd_;
    HDC hDc_;
};

Window::Window(Size width, Size height) : impl_(new Impl(width, height)) {}

Window::~Window() {}

WindowHandle Window::getWindowHandle() const { return impl_->getWindowHandle(); }

ViewHandle Window::getViewHandle() const { return impl_->getViewHandle(); }

Window::SPtr Window::create(Size width, Size height) {
    struct Creator : public Window {
        Creator(Size width, Size height) : Window(width, height) {}
    };

    auto p = std::make_shared< Creator >(width, height);
    return std::move(p);
}
}
}
#endif TEMP_PLATFORM_WINDOWS
