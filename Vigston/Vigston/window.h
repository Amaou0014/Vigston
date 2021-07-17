#pragma once

#include <windows.h>

// �E�B���h�E�N���X
class Window
{
    // �E�B���h�E�̖��O���i�[����z��
    TCHAR WINDOW_CLASS_NAME[1024];

    // �E�B���h�E���b�Z�[�W������
    static LRESULT CALLBACK StaticWndProc(
        HWND hwnd,
        UINT msg,
        WPARAM wp,
        LPARAM lp);
public:
    HWND hwnd;         // �E�B���h�E�I�u�W�F�N�g
    int x;             // �E�B���h�E��X���W
    int y;             // �E�B���h�E��Y���W
    int w;             // �E�B���h�E�̉���
    int h;             // �E�B���h�E�̏c��
public:
    // �R���X�g���N�^
    Window();
    // �f�X�g���N�^
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

    // �E�B���h�E�I�u�W�F�N�g�擾
    HWND GetHWND()const { return hwnd; }

    // �E�B���h�E�쐬
    bool Create_Window(
        LPCTSTR name,   // �E�B���h�E��
        DWORD dwStyle,         // �E�B���h�E�X�^�C��
        HWND hWndParent,      // �e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
        HMENU hMenu            // ���j���[�n���h���܂��͎q�E�B���h�E ID
    );
};