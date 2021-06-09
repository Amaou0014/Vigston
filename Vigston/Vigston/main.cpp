#include "vigston.h"


// ���b�Z�[�W����
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
		// �E�B���h�E���j�����ꂽ�Ƃ�
	case WM_DESTROY:
		PostQuitMessage(0);	// WM_QUIT���b�Z�[�W�����b�Z�[�W�L���[�ɑ���
		return 0;
	}
	// �f�t�H���g�̃��b�Z�[�W����
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

// WinMain�֐��i���̊֐��������j
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Vigston vigston;

	vigston.WC_BASIC = _T("BASIC_WINDOW");
	// �V���v���E�B���h�E�N���X�ݒ�
	vigston.wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,WndProc, 0,0,hInstance,
		(HICON)LoadImage(NULL,MAKEINTRESOURCE(IDI_APPLICATION),IMAGE_ICON,0,0,LR_DEFAULTSIZE | LR_SHARED),
		(HCURSOR)LoadImage(NULL,MAKEINTRESOURCE(IDC_ARROW),IMAGE_CURSOR,0,0,LR_DEFAULTSIZE | LR_SHARED),
		(HBRUSH)GetStockObject(WHITE_BRUSH), NULL, vigston.WC_BASIC , NULL };

	// �V���v���E�B���h�E�N���X�쐬
	if (!RegisterClassEx(&vigston.wcex))
		return false;

	// �E�B���h�E���A�����̓f�B�X�v���C�Ɉˑ�����B���ʂ�4:3
	vigston.WINDOW_WIDTH = 640;
	vigston.WINDOW_HEIGHT = 480;

	// �E�B���h�E�̍쐬
	vigston.hWnd = CreateWindowEx(0, vigston.WC_BASIC,
		_T("VigstonApp"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, vigston.WINDOW_WIDTH, vigston.WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	vigston.Init(vigston.hWnd);

	vigston.Start();

	// ���b�Z�[�W���[�v
	MSG msg = {};
	while (msg.message != WM_QUIT) {
		// �A�v���P�[�V�����ɑ����Ă��郁�b�Z�[�W�����b�Z�[�W�L���[����擾����
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			DispatchMessage(&msg);	// �A�v���P�[�V�����̊e�E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W��]������
		}
		// ���b�Z�[�W���������Ă��Ȃ��Ƃ�
		else {
			// �����Ɋe�N���X��Update������
			vigston.Update();
		}
	}


	return 0;
}