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
	LoadSound((TCHAR*)_T("Resources/maou_retoro_1.wav"), &wave_retoro1, &sb_retolo1);
	LoadSound((TCHAR*)_T("Resources/maou_retoro_2.wav"), &wave_retoro2, &sb_retolo2);

	SetSprite(100, 100, 128, 128, 0, &sprite);

	//sb_retolo2.Play(true);
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

		if (keyboard.GetKey('W'))
		{
			sprite.UpdatePos(0,-1);
		}
		if (keyboard.GetKey('A'))
		{
			sprite.UpdatePos(-1, 0);
		}
		if (keyboard.GetKey('S'))
		{
			sprite.UpdatePos(0, 1);
		}
		if (keyboard.GetKey('D'))
		{
			sprite.UpdatePos(1, 0);
		}

		if (keyboard.PushKey('T'))
		{
			sb_retolo1.Play(false);
		}

		if (keyboard.PushKey('P'))
		{
			SetVolume(-10000, &sb_retolo1);
		}

		if (keyboard.PushKey('O'))
		{
			SetVolume(0, &sb_retolo1);
		}

		sprite.Draw(direct3d.pDevice3D, texture.pTexture);

		// �`��I��
		direct3d.pDevice3D->EndScene();
	}
	// �`�攽�f
	direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);
}

bool Vigston::LoadTexture(TCHAR* _name, Texture* _texture)
{
	return _texture->Load(direct3d.pDevice3D, _name);
}

bool Vigston::LoadSound(TCHAR* name, Wave* wave, SoundBuffer* sb)
{
	if (wave->Load(name) &&
		sb->Create(directsound.pDirectSound8, &wave->WaveFormat, wave->WaveData, wave->DataSize))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Vigston::SetVolume(long _volume, SoundBuffer* sb)
{
	sb->SetVolume(_volume);
}

long Vigston::GetVolume(SoundBuffer* sb)
{
	return sb->GetVolume();
}

void Vigston::SetSprite(float x, float y, int width, int height, float rotate, Sprite* _sprite)
{
	_sprite->SetPos(x, y);
	_sprite->SetWidth(width, height);
	_sprite->SetRotate(rotate);
}