#include "vigston.h"

Vigston::Vigston()
{

}

Vigston::~Vigston()
{

}

void Vigston::Init(HWND hWnd)
{
	// Direct3Dì¬
	direct3d.Create(hWnd, WINDOW_WIDTH, WINDOW_HEIGHT);
	// DirectSoundì¬
	directsound.Create(hWnd);

	// «ŠeƒvƒƒOƒ‰ƒ€‚Ì‰Šú‰»‚ð“®‚©‚·«
}

void Vigston::Start()
{

}

// ƒƒCƒ“ƒ‹[ƒv
void Vigston::Update()
{
	// •`‰æŠJŽn
	if (SUCCEEDED(direct3d.pDevice3D->BeginScene()))
	{
		DWORD ClearColor = 0xff808080;	// ”wŒiƒNƒŠƒAF
		// ”wŒiƒNƒŠƒA
		direct3d.pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, ClearColor, 1.0f, 0);

		// «‚±‚±‚ÉŠeƒvƒƒOƒ‰ƒ€‚ÌUpdateŠÖ”‚ð“®‚©‚·«

		// •`‰æI—¹
		direct3d.pDevice3D->EndScene();
	}
	// •`‰æ”½‰f
	direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);
}

void Vigston::WindowCreate(const char* name, int width, int height)
{
	hWnd = CreateWindowEx(0, WC_BASIC,
		_T("VigstonApp"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
}