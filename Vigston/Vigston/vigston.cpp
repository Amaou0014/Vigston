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
	LoadTexture((TCHAR*)_T("Resources/Slime.png"), &texture);

	SetSprite(100, 100, 128, 128, 0, &sprite);
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

		// �������Ɋe�v���O�����𓮂�����
		// �X�v���C�g�`��

		sprite.Draw(direct3d.pDevice3D, texture.pTexture);

		// �`��I��
		direct3d.pDevice3D->EndScene();
	}
	// �`�攽�f
	direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);
}

bool Vigston::LoadTexture(TCHAR* _name, Texture* _texture)
{
	if (_texture->Load(direct3d.pDevice3D, _name))
	{
		// �ǂݍ��ݐ���
		return true;
	}
	else
	{
		// �ǂݍ��ݎ��s
		return false;
	}
}

void Vigston::SetSprite(float x, float y, int width, int height, float rotate, Sprite* _sprite)
{
	_sprite->SetPos(x, y);
	_sprite->SetWidth(width, height);
	_sprite->SetRotate(rotate);
}