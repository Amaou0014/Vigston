#include "window.h"
#include <tchar.h>

Window::Window()
{
}
Window::~Window()
{

}
// ウィンドウを作成する
bool Window::Set_Window(const TCHAR* name, const HINSTANCE hInst)
{
    _tcscpy_s(WINDOW_CLASS_NAME, name);
    hInstance = hInst;
    WNDCLASSEX wc;

    // ウィンドウクラスの情報を設定
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = Window::StaticWndProc; // ウィンドウプロシージャ
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;                     // インスタンスハンドル
    wc.hIcon = (HICON)LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WINDOW_CLASS_NAME;     // ウィンドウクラス名

    // ウィンドウクラスを登録する
    if (RegisterClassEx(&wc) == 0) { return false; }

    return true;
}
bool Window::Create_Window(
    LPCTSTR name, // ウィンドウ名
    DWORD dwStyle,        // ウィンドウスタイル
    int x,                // ウィンドウの横方向の位置
    int y,                // ウィンドウの縦方向の位置
    int _width,           // ウィンドウの幅
    int _height,          // ウィンドウの高さ
    HWND hWndParent,      // 親ウィンドウまたはオーナーウィンドウのハンドル
    HMENU hMenu           // メニューハンドルまたは子ウィンドウ ID
) {
    hwnd = CreateWindow(
        WINDOW_CLASS_NAME,      // ウィンドウクラス名
        name,         // タイトルバーに表示する文字列
        dwStyle,            //  ウィンドウの種類
        x,                  // ウィンドウを表示する位置（X座標）
        y,                  // ウィンドウを表示する位置（Y座標）
        _width,               // ウィンドウの幅
        _height,            // ウィンドウの高さ
        hWndParent,            // 親ウィンドウのウィンドウハンドル
        hMenu,               // メニューハンドル
        hInstance,         // インスタンスハンドル
        this               // その他の作成データ
    );

    width = _width;
    height = _height;

    if (hwnd == nullptr)
        return false;

    return true;
}
LRESULT  Window::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wp, lp);
}
LRESULT CALLBACK Window::StaticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    Window* This = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    if (!This) {//取得できなかった(ウィンドウ生成中)場合
        if (message == WM_CREATE) {
            This = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
            if (This) {
                SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)This);
                return This->WndProc(hWnd, message, wParam, lParam);
            }
        }
    }
    else {//取得できた場合(ウィンドウ生成後)
        return This->WndProc(hWnd, message, wParam, lParam);
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}