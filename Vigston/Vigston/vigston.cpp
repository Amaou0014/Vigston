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
	Load_Texture((TCHAR*)_T("Resources/Slime.png"), &texture);
	Load_Sound((TCHAR*)_T("Resources/maou_retoro_1.wav"), &wave_retoro1, &sb_retolo1);
	Load_Sound((TCHAR*)_T("Resources/maou_retoro_2.wav"), &wave_retoro2, &sb_retolo2);

	Set_Sprite(100, 100, 128, 128, 0, &sprite);
}

// ƒƒCƒ“ƒ‹[ƒv
void Vigston::Update()
{
	// •`‰æŠJŽn
	if (Begine_Scene())
	{
		// ”wŒiFƒZƒbƒg
		Set_BackColor(0xff808080);
		// ”wŒiƒNƒŠƒA
		Clear_Screen();

		// «‚±‚±‚ÅŠeƒvƒƒOƒ‰ƒ€‚ð“®‚©‚·«

		if (GetKey('W'))
		{
			Move_Sprite(0, -1, 0, &sprite);
		}
		if (GetKey('A'))
		{
			Move_Sprite(-1, 0, 0, &sprite);
		}
		if (GetKey('S'))
		{
			Move_Sprite(0, 1, 0, &sprite);
		}
		if (GetKey('D'))
		{
			Move_Sprite(1, 0, 0, &sprite);
		}

		if (PushKey('T'))
		{
			Play_Sound(false, &sb_retolo1);
		}

		if (PushKey('P'))
		{
			Set_Volume(-10000, &sb_retolo1);
		}

		if (PushKey('O'))
		{
			Set_Volume(0, &sb_retolo1);
		}

		// •`‰æˆ—
		sprite.Draw(direct3d.pDevice3D, texture.pTexture);

		// •`‰æI—¹
		End_Scene();
	}
	// •`‰æ”½‰f
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