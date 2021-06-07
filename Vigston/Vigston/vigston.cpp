#include "vigston.h"

Vigston::Vigston()
{

}

Vigston::~Vigston()
{

}

void Vigston::Init(HWND hWnd)
{
	// Direct3D作成
	direct3d.Create(hWnd, WINDOW_WIDTH, WINDOW_HEIGHT);
	// DirectSound作成
	directsound.Create(hWnd);

	// ↓各プログラムの初期化を動かす↓
}

void Vigston::Start()
{

}

// メインループ
void Vigston::Update()
{
	// 描画開始
	if (SUCCEEDED(direct3d.pDevice3D->BeginScene()))
	{
		DWORD ClearColor = 0xff808080;	// 背景クリア色
		// 背景クリア
		direct3d.pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, ClearColor, 1.0f, 0);

		// ↓ここに各プログラムのUpdate関数を動かす↓

		// 描画終了
		direct3d.pDevice3D->EndScene();
	}
	// 描画反映
	direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);
}