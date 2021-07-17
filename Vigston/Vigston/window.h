#pragma once

#include <windows.h>

// ウィンドウクラス
class Window
{
    // ウィンドウの名前を格納する配列
    TCHAR WINDOW_CLASS_NAME[1024];

    // ウィンドウメッセージを処理
    static LRESULT CALLBACK StaticWndProc(
        HWND hwnd,
        UINT msg,
        WPARAM wp,
        LPARAM lp);
public:
    HWND hwnd;         // ウィンドウオブジェクト
    int x;             // ウィンドウのX座標
    int y;             // ウィンドウのY座標
    int w;             // ウィンドウの横幅
    int h;             // ウィンドウの縦幅
public:
    // コンストラクタ
    Window();
    // デストラクタ
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

    // ウィンドウオブジェクト取得
    HWND GetHWND()const { return hwnd; }

    // ウィンドウ作成
    bool Create_Window(
        LPCTSTR name,   // ウィンドウ名
        DWORD dwStyle,         // ウィンドウスタイル
        HWND hWndParent,      // 親ウィンドウまたはオーナーウィンドウのハンドル
        HMENU hMenu            // メニューハンドルまたは子ウィンドウ ID
    );
};