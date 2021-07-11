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
    int x;
    int y;
    int w;
    int h;
public:
    Window();
    virtual ~Window();

    // ウィンドウ初期化
    void Init(const TCHAR* name, LPCTSTR win_name, DWORD dwStyle, HWND hWndParent, HMENU hMenu);

    // ウィンドウセット
    bool Set_Window(const TCHAR* name);
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

    // ウィンドウ作成
    bool Create_Window(
        LPCTSTR name,   // ウィンドウ名
        DWORD dwStyle,         // ウィンドウスタイル
        HWND hWndParent,      // 親ウィンドウまたはオーナーウィンドウのハンドル
        HMENU hMenu            // メニューハンドルまたは子ウィンドウ ID
    );
};