#include "vigston.h"

Vigston::Vigston()
{

}

Vigston::~Vigston()
{

}

void Vigston::Init(HINSTANCE hInstance)
{
	Set_Window(_T("BASIC_WINDOW"), hInstance);
	Create_Window(_T("VigstonApp"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, nullptr, nullptr);
	// Direct3D作成
	direct3d.Create(window.hwnd, window.w, window.h);
	// DirectSound作成
	directsound.Create(window.hwnd);
	// ↓各プログラムの初期化を動かす↓
}

void Vigston::Set_Window(const TCHAR* name, const HINSTANCE hInst)
{
	window.Set_Window(name, hInst);
}

void Vigston::Set_Window_Pos(int x, int y)
{
	window.x = x;
	window.y = y;
}

void Vigston::Set_Window_Size(int w, int h)
{
	window.w = w;
	window.h = h;
}

void Vigston::Create_Window(LPCTSTR name, DWORD dwStyle,HWND hWndParent, HMENU hMenu)
{
	window.Create_Window(name, dwStyle, hWndParent, hMenu);
}

bool Vigston::GameQuit()
{
	if (msg.message != WM_QUIT)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Vigston::ProcessMessage()
{
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
		DispatchMessage(&msg);	// アプリケーションの各ウィンドウプロシージャにメッセージを転送する
		return true;
	}
	else
	{
		return false;
	}
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