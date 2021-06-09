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
	LoadTexture((TCHAR*)_T("Resources/Slime.png"), &texture);
	LoadSound((TCHAR*)_T("Resources/maou _retoro_1.wav"), &wave, &sb);

	SetSprite(100, 100, 128, 128, 0, &sprite);
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

		// ↓ここに各プログラムを動かす↓
		// スプライト描画

		if (GetKey('W'))
		{
			sprite.UpdatePos(0,-1);
		}
		if (GetKey('A'))
		{
			sprite.UpdatePos(-1, 0);
		}
		if (GetKey('S'))
		{
			sprite.UpdatePos(0, 1);
		}
		if (GetKey('D'))
		{
			sprite.UpdatePos(1, 0);
		}

		if (PushKey('T'))
		{
			sb.Play(false);
			sprite.UpdateRotate(10);
		}
		if (ReleaseKey('T'))
		{
			sb.Play(false);
			sprite.UpdateRotate(-10);
		}

		sprite.Draw(direct3d.pDevice3D, texture.pTexture);

		// 描画終了
		direct3d.pDevice3D->EndScene();
	}
	// 描画反映
	direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);
}

bool Vigston::LoadTexture(TCHAR* _name, Texture* _texture)
{
	return _texture->Load(direct3d.pDevice3D, _name);
}

bool Vigston::LoadSound(TCHAR* name, Wave* wave, SoundBuffer* sb)
{
	if (wave->Load(name) &&
		sb->Create(directsound.pDirectSound8, wave->WaveFormat, wave->WaveData, wave->DataSize))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Vigston::SetSprite(float x, float y, int width, int height, float rotate, Sprite* _sprite)
{
	_sprite->SetPos(x, y);
	_sprite->SetWidth(width, height);
	_sprite->SetRotate(rotate);
}