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
    LPCTSTR name, // �E�B���h�E��
    DWORD dwStyle,        // �E�B���h�E�X�^�C��
    HWND hWndParent,      // �e�E�B���h�E�܂��̓I�[�i�[�E�B���h�E�̃n���h��
    HMENU hMenu           // ���j���[�n���h���܂��͎q�E�B���h�E ID
) {
    hwnd = CreateWindow(
        WINDOW_CLASS_NAME,      // �E�B���h�E�N���X��
        name,         // �^�C�g���o�[�ɕ\�����镶����
        dwStyle,            //  �E�B���h�E�̎��
        x,                  // �E�B���h�E��\������ʒu�iX���W�j
        y,                  // �E�B���h�E��\������ʒu�iY���W�j
        w,               // �E�B���h�E�̕�
        h,            // �E�B���h�E�̍���
        hWndParent,            // �e�E�B���h�E�̃E�B���h�E�n���h��
        hMenu,               // ���j���[�n���h��
        hInstance,         // �C���X�^���X�n���h��
        this               // ���̑��̍쐬�f�[�^
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
    if (!This) {//�擾�ł��Ȃ�����(�E�B���h�E������)�ꍇ
        if (message == WM_CREATE) {
            This = (Window*)((LPCREATESTRUCT)lParam)->lpCreateParams;
            if (This) {
                SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)This);
                return This->WndProc(hwnd, message, wParam, lParam);
            }
        }
    }
    else {//�擾�ł����ꍇ(�E�B���h�E������)
        return This->WndProc(hwnd, message, wParam, lParam);
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}