#pragma once
#include <windows.h>
class Window
{
    TCHAR WINDOW_CLASS_NAME[1024];

    static LRESULT CALLBACK StaticWndProc(
        HWND hwnd,
        UINT msg,
        WPARAM wp,
        LPARAM lp);
public:
    HWND hwnd;
    HINSTANCE hInstance;
    int x;
    int y;
    int w;
    int h;
public:
    Window();
    virtual ~Window();

    // ウィンドウセット
    bool Set_Window(const TCHAR* name, const HINSTANCE hInst);
    // ウィンドウ座標セット
    void Set_Pos(int _x, int _y);
    // ウィンドウX座標取得
    int Get_Pos_X();
    // ウィンドウY座標取得
    int Get_Pos_Y();
    // ウィンドウサイズセット
    void Set_Size(int _w, int _h);
    // ウィンドウ横幅ゲット
    int Get_Width();
    // ウィンドウ縦幅ゲット
    int Get_Height();

    // ウィンドウプロシージャ
    virtual LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

    HWND GetHWND()const { return hwnd; }
    HINSTANCE GetHINSTANCE()const { return hInstance; }

    // ウィンドウ作成
    bool Create_Window(
        LPCTSTR name,   // ウィンドウ名
        DWORD dwStyle,         // ウィンドウスタイル
        HWND hWndParent,      // 親ウィンドウまたはオーナーウィンドウのハンドル
        HMENU hMenu            // メニューハンドルまたは子ウィンドウ ID
    );
};