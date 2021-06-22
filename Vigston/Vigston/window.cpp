#include "window.h"
#include <tchar.h>

Window::Window()
{
}
Window::~Window()
{

}
// �E�B���h�E���쐬����
bool Window::Set_Window(const TCHAR* name, const HINSTANCE hInst)
{
    _tcscpy_s(WINDOW_CLASS_NAME, name);
    hInstance = hInst;
    WNDCLASSEX wc;

    // �E�B���h�E�N���X�̏���ݒ�
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = Window::StaticWndProc; // �E�B���h�E�v���V�[�W��
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;                     // �C���X�^���X�n���h��
    wc.hIcon = (HICON)LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = wc.hIcon;
    wc.hCursor = (HCURSOR)LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = WINDOW_CLASS_NAME;     // �E�B���h�E�N���X��

    // �E�B���h�E�N���X��o�^����
    if (RegisterClassEx(&wc) == 0) { return false; }

    return true;
}
bool Window::Create_Window(
    LPCTSTR name, // �E�B���h�E��
    DWORD dwStyle,        // �E�B���h�E�X�^�C��
    int x,                // �E�B���h�E�̉������̈ʒu
    int y,                // �E�B���h�E�̏c�����̈ʒu
    int _width,           // �E�B���h�E�̕�
    int _height,          // �E�B���h�E�̍���
    HWND hWndParent,      // �e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
    HMENU hMenu           // ���j���[�n���h���܂��͎q�E�B���h�E ID
) {
    hwnd = CreateWindow(
        WINDOW_CLASS_NAME,      // �E�B���h�E�N���X��
        name,         // �^�C�g���o�[�ɕ\�����镶����
        dwStyle,            //  �E�B���h�E�̎��
        x,                  // �E�B���h�E��\������ʒu�iX���W�j
        y,                  // �E�B���h�E��\������ʒu�iY���W�j
        _width,               // �E�B���h�E�̕�
        _height,            // �E�B���h�E�̍���
        hWndParent,            // �e�E�B���h�E�̃E�B���h�E�n���h��
        hMenu,               // ���j���[�n���h��
        hInstance,         // �C���X�^���X�n���h��
        this               // ���̑��̍쐬�f�[�^
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
    if (!This) {//�擾�ł��Ȃ�����(�E�B���h�E������)�ꍇ
        if (message == WM_CREATE) {
            This = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
            if (This) {
                SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)This);
                return This->WndProc(hWnd, message, wParam, lParam);
            }
        }
    }
    else {//�擾�ł����ꍇ(�E�B���h�E������)
        return This->WndProc(hWnd, message, wParam, lParam);
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}