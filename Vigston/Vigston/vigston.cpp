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
	Load_Texture((TCHAR*)_T("Resources/Slime.png"), &texture);
	Load_Sound((TCHAR*)_T("Resources/maou_retoro_1.wav"), &wave_retoro1, &sb_retolo1);
	Load_Sound((TCHAR*)_T("Resources/maou_retoro_2.wav"), &wave_retoro2, &sb_retolo2);

	Set_Sprite(100, 100, 128, 128, 0, &sprite);
}

// ���C�����[�v
void Vigston::Update()
{
	// �����_�����O�J�n
	if (Begine_Scene())
	{
		// �w�i�F�Z�b�g
		Set_BackColor(0xff808080);
		// �w�i�N���A
		Clear_Screen();

		// �������Ŋe�v���O�����𓮂�����
		keyboard.GetKeyState();

		if (keyboard.GetKey(KEY_CODE_W))
		{
			Move_Sprite(0, -1, 0, &sprite);
		}
		if (keyboard.GetKey(KEY_CODE_A))
		{
			Move_Sprite(-1, 0, 0, &sprite);
		}
		if (keyboard.GetKey(KEY_CODE_S))
		{
			Move_Sprite(0, 1, 0, &sprite);
		}
		if (keyboard.GetKey(KEY_CODE_D))
		{
			Move_Sprite(1, 0, 0, &sprite);
		}
		if (keyboard.PushKey(KEY_CODE_R))
		{
			Move_Sprite(0, 0, -1, &sprite);
		}
		if (keyboard.ReleaseKey(KEY_CODE_R))
		{
			Move_Sprite(0, 0, 1, &sprite);
		}
		if (keyboard.PushKey(KEY_CODE_T))
		{
			Move_Sprite(0, 0, 1, &sprite);
		}

		// �`�揈��
		Draw(&texture, &sprite);

		// �����_�����O�I��
		End_Scene();
	}
	// �`�攽�f
	direct3d.pDevice3D->Present(NULL, NULL, NULL, NULL);
}

void Vigston::Set_BackColor(unsigned int color)
{
	backColor = color;
}

void Vigston::Clear_Screen()
{
	direct3d.pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, backColor, 1.0f, 0);
}

bool Vigston::Begine_Scene()
{
	return SUCCEEDED(direct3d.pDevice3D->BeginScene());
}

bool Vigston::End_Scene()
{
	return SUCCEEDED(direct3d.pDevice3D->EndScene());
}


bool Vigston::Load_Texture(TCHAR* _name, Texture* _texture)
{
	return _texture->Load(direct3d.pDevice3D, _name);
}

bool Vigston::Load_Sound(TCHAR* name, Wave* wave, SoundBuffer* sb)
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

void Vigston::Play_Sound(bool isLoop, SoundBuffer* sb)
{
	sb->Play(isLoop);
}

void Vigston::Set_Volume(long _volume, SoundBuffer* sb)
{
	sb->SetVolume(_volume);
}

long Vigston::Get_Volume(SoundBuffer* sb)
{
	return sb->GetVolume();
}

void Vigston::Set_Sprite(float x, float y, int width, int height, float rotate, Sprite* sprite)
{
	sprite->SetPos(x, y);
	sprite->SetWidth(width, height);
	sprite->SetRotate(rotate);
}

void Vigston::Move_Sprite(float x, float y, float rotate, Sprite* sprite)
{
	sprite->MovePos(x,y);
	sprite->MoveRotate(rotate);
}

void Vigston::Draw(Texture* texture, Sprite* sprite)
{
	sprite->Draw(direct3d.pDevice3D, texture->pTexture);
}