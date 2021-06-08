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
	LoadTexture((TCHAR*)_T("Resources/Slime.png"), &texture);

	SetSprite(100, 100, 128, 128, 0, &sprite);
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

		// «‚±‚±‚ÉŠeƒvƒƒOƒ‰ƒ€‚ð“®‚©‚·«
		// ƒXƒvƒ‰ƒCƒg•`‰æ

		sprite.Draw(direct3d.pDevice3D, texture.pTexture);

		// •`‰æI—¹
		direct3d.pDevice3D->EndScene();
	}
	// •`‰æ”½‰f
	direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);
}

bool Vigston::LoadTexture(TCHAR* _name, Texture* _texture)
{
	if (_texture->Load(direct3d.pDevice3D, _name))
	{
		// “Ç‚Ýž‚Ý¬Œ÷
		return true;
	}
	else
	{
		// “Ç‚Ýž‚ÝŽ¸”s
		return false;
	}
}

void Vigston::SetSprite(float x, float y, int width, int height, float rotate, Sprite* _sprite)
{
	_sprite->SetPos(x, y);
	_sprite->SetWidth(width, height);
	_sprite->SetRotate(rotate);
}