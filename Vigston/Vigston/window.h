#pragma once
#include <windows.h>
class Window
{
    TCHAR WINDOW_CLASS_NAME[1024];

    static LRESULT CALLBACK StaticWndProc(
        HWND hWnd,
        UINT msg,
        WPARAM wp,
        LPARAM lp);
public:
    HWND hwnd;
    HINSTANCE hInstance;

    int width;
    int height;
public:
    Window();
    virtual ~Window();

    // ウィンドウセット
    bool Set_Window(const TCHAR* name, const HINSTANCE hInst);

    // ウィンドウプロシージャ
    virtual LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

    HWND GetHWND()const { return hwnd; }
    HINSTANCE GetHINSTANCE()const { return hInstance; }

    // ウィンドウ作成
    bool Create_Window(
        LPCTSTR name,   // ウィンドウ名
        DWORD dwStyle,         // ウィンドウスタイル
        int x,               // ウィンドウの横方向の位置
        int y,               // ウィンドウの縦方向の位置
        int width,            // ウィンドウの幅
        int height,         // ウィンドウの高さ
        HWND hWndParent,      // 親ウィンドウまたはオーナーウィンドウのハンドル
        HMENU hMenu            // メニューハンドルまたは子ウィンドウ ID
    );
};