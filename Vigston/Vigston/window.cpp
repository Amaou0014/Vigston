#include "window.h"
#include <tchar.h>

Window::Window()
{
    x = 100;
    y = 100;
    w = 640;
    h = 480;
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

void Window::Set_Pos(int _x, int _y)
{
    x = _x;
    y = _y;
}

int Window::Get_Pos_X()
{
    return x;
}

int Window::Get_Pos_Y()
{
    return y;
}

void Window::Set_Size(int _width, int _height)
{
    w = _width;
    h = _height;
}

int Window::Get_Width()
{
    return w;
}

int Window::Get_Height()
{
    return h;
}

bool Window::Create_Window(
    LPCTSTR name, // ウィンドウ名
    DWORD dwStyle,        // ウィンドウスタイル
    HWND hWndParent,      // 親ウィンドウまたはオーナーウィンドウのハンドル
    HMENU hMenu           // メニューハンドルまたは子ウィンドウ ID
) {
    hwnd = CreateWindow(
        WINDOW_CLASS_NAME,      // ウィンドウクラス名
        name,         // タイトルバーに表示する文字列
        dwStyle,            //  ウィンドウの種類
        x,                  // ウィンドウを表示する位置（X座標）
        y,                  // ウィンドウを表示する位置（Y座標）
        w,               // ウィンドウの幅
        h,            // ウィンドウの高さ
        hWndParent,            // 親ウィンドウのウィンドウハンドル
        hMenu,               // メニューハンドル
        hInstance,         // インスタンスハンドル
        this               // その他の作成データ
    );

    if (hwnd == nullptr)
        return false;

    return true;
}
LRESULT  Window::WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_KEYDOWN:
        switch (wp)
        {
        case VK_ESCAPE:
            switch (MessageBox(hwnd, _T("Quit the application"), _T("Message"), MB_OKCANCEL))
            {
            case IDOK:
                PostQuitMessage(0);
                return 0;
            case IDCANCEL:
                return 0;
            default:
                break;
            }
            return 0;
        default:
            break;
        }
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}
LRESULT CALLBACK Window::StaticWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    Window* This = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    if (!This) {//取得できなかった(ウィンドウ生成中)場合
        if (message == WM_CREATE) {
            This = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
            if (This) {
                SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)This);
                return This->WndProc(hwnd, message, wParam, lParam);
            }
        }
    }
    else {//取得できた場合(ウィンドウ生成後)
        return This->WndProc(hwnd, message, wParam, lParam);
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}