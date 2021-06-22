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

    // �E�B���h�E�Z�b�g
    bool Set_Window(const TCHAR* name, const HINSTANCE hInst);

    // �E�B���h�E�v���V�[�W��
    virtual LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

    HWND GetHWND()const { return hwnd; }
    HINSTANCE GetHINSTANCE()const { return hInstance; }

    // �E�B���h�E�쐬
    bool Create_Window(
        LPCTSTR name,   // �E�B���h�E��
        DWORD dwStyle,         // �E�B���h�E�X�^�C��
        int x,               // �E�B���h�E�̉������̈ʒu
        int y,               // �E�B���h�E�̏c�����̈ʒu
        int width,            // �E�B���h�E�̕�
        int height,         // �E�B���h�E�̍���
        HWND hWndParent,      // �e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
        HMENU hMenu            // ���j���[�n���h���܂��͎q�E�B���h�E ID
    );
};