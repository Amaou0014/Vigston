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

    // �E�B���h�E������
    void Init(const TCHAR* name, LPCTSTR win_name, DWORD dwStyle, HWND hWndParent, HMENU hMenu);

    // �E�B���h�E�Z�b�g
    bool Set_Window(const TCHAR* name);
    // �E�B���h�E���W�Z�b�g
    void Set_Pos(int _x, int _y);
    // �E�B���h�EX���W�擾
    int Get_Pos_X();
    // �E�B���h�EY���W�擾
    int Get_Pos_Y();
    // �E�B���h�E�T�C�Y�Z�b�g
    void Set_Size(int _w, int _h);
    // �E�B���h�E�����Q�b�g
    int Get_Width();
    // �E�B���h�E�c���Q�b�g
    int Get_Height();

    // �E�B���h�E�v���V�[�W��
    virtual LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

    HWND GetHWND()const { return hwnd; }

    // �E�B���h�E�쐬
    bool Create_Window(
        LPCTSTR name,   // �E�B���h�E��
        DWORD dwStyle,         // �E�B���h�E�X�^�C��
        HWND hWndParent,      // �e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
        HMENU hMenu            // ���j���[�n���h���܂��͎q�E�B���h�E ID
    );
};