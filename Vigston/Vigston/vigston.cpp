#include "vigston.h"

Vigston::Vigston()
{

}

Vigston::~Vigston()
{

}

void Vigston::Init(HWND hWnd)
{
	// Direct3D�쐬
	direct3d.Create(hWnd, WINDOW_WIDTH, WINDOW_HEIGHT);
	// DirectSound�쐬
	directsound.Create(hWnd);

	// ���e�v���O�����̏������𓮂�����
}

void Vigston::Start()
{

}

// ���C�����[�v
void Vigston::Update()
{
	// �`��J�n
	if (SUCCEEDED(direct3d.pDevice3D->BeginScene()))
	{
		DWORD ClearColor = 0xff808080;	// �w�i�N���A�F
		// �w�i�N���A
		direct3d.pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, ClearColor, 1.0f, 0);

		// �������Ɋe�v���O������Update�֐��𓮂�����

		// �`��I��
		direct3d.pDevice3D->EndScene();
	}
	// �`�攽�f
	direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);
}

void Vigston::WindowCreate(const char* name, int width, int height)
{
	hWnd = CreateWindowEx(0, WC_BASIC,
		_T("VigstonApp"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
}