#include "vigston.h"

Vigston::Vigston()
{
	direct3d = new Direct3D();
	sound = new Sound();
	image = new Image();
	text = new Text();
	device = new Device();
	window = new Window();
}

Vigston::~Vigston()
{
	delete direct3d;
	delete sound;
	delete image;
	delete text;
	delete device;
	delete window;
}

void Vigston::Init()
{
	Set_Window(_T("BASIC_WINDOW"));
	Create_Window(_T("VigstonApp"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, nullptr, nullptr);
	// Direct3D作成
	direct3d->Create(window->hwnd, window->w, window->h);
	// DirectSound作成
	sound->Create_SoundDevice(window->hwnd);
	// ↓各プログラムの初期化を動かす↓
}

void Vigston::Set_Window(const TCHAR* name)
{
	window->Set_Window(name);
}

void Vigston::Set_Window_Pos(int x, int y)
{
	window->x = x;
	window->y = y;
}

void Vigston::Set_Window_Size(int w, int h)
{
	window->w = w;
	window->h = h;
}

void Vigston::Create_Window(LPCTSTR name, DWORD dwStyle,HWND hWndParent, HMENU hMenu)
{
	window->Create_Window(name, dwStyle, hWndParent, hMenu);
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
	direct3d->pDevice3D->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, backColor, 1.0f, 0);
}

bool Vigston::Begine_Scene()
{
	return SUCCEEDED(direct3d->pDevice3D->BeginScene());
}

bool Vigston::End_Scene()
{
	return SUCCEEDED(direct3d->pDevice3D->EndScene());
}

void Vigston::ScreenFlip()
{
	direct3d->pDevice3D->Present(NULL, NULL, NULL, NULL);
}


bool Vigston::Load_Image(const char* keyname, TCHAR* _name, float x, float y, int width, int height, float rotate)
{
	return image->Load(keyname, direct3d->pDevice3D, _name, x, y, width, height, rotate);
}

bool Vigston::LoadDiv_Image(const char* keyname, TCHAR* name, float x, float y, int width, int height, float rotate, unsigned int DivU, unsigned int DivV)
{
	return image->LoadDiv_Image(keyname,direct3d->pDevice3D, name, x, y, width, height, rotate, DivU, DivV);
}

void Vigston::Set_Image(const char* keyname, float x, float y, int width, int height, float rotate)
{
	image->Set_Pos(keyname, x, y);
	image->Set_Size(keyname, width, height);
	image->Set_Rotate(keyname, rotate);
}

void Vigston::Move_Image(const char* keyname, float x, float y, float rotate)
{
	image->Move_Pos(keyname, x, y);
	image->Move_Rotate(keyname, rotate);
}

float Vigston::Get_Image_PosX(const char* keyname)
{
	return image->Get_PosX(keyname);
}

float Vigston::Get_Image_PosY(const char* keyname)
{
	return image->Get_PosY(keyname);
}

void Vigston::Draw_Image(const char* keyname, bool isTurn)
{
	image->SetRenderState(direct3d->pDevice3D, image->RENDER_ALPHATEST);
	image->Draw(keyname, direct3d->pDevice3D, isTurn);
}

void Vigston::DrawDiv_Image(const char* keyname, unsigned int NumU, unsigned int NumV, bool isTurn)
{
	image->DrawDiv(keyname, direct3d->pDevice3D, NumU, NumV, isTurn);
}

bool Vigston::Load_Sound(const char* keyname, TCHAR* name)
{
	if (sound->Load_Wave(name) &&
		sound->Create_Buffer(keyname))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Vigston::Play_Sound(const char* keyname, bool isLoop)
{
	sound->Play(keyname, isLoop);
}

void Vigston::Set_Volume(const char* keyname, long _volume)
{
	sound->SetVolume(keyname, _volume);
}

long Vigston::Get_Volume(const char* keyname)
{
	return sound->GetVolume(keyname);
}

bool Vigston::Create_Font(int size)
{
	return text->Create(direct3d->pDevice3D, size);
}

void Vigston::Draw_Font(int x, int y, DWORD color, const TCHAR* str...)
{
	va_list args;
	va_start(args, str);   // 可変引数の最初の要素を格納する
	text->Draw(x, y, color, str, args);
}

void Vigston::GetKeyState()
{
	device->GetKeyState();
}

bool Vigston::GetKey(unsigned char keycode)
{
	return device->GetKey(keycode);
}

bool Vigston::PushKey(unsigned char keycode)
{
	return device->PushKey(keycode);
}

bool Vigston::ReleaseKey(unsigned char keycode)
{
	return device->ReleaseKey(keycode);
}

void Vigston::GetMouseState()
{
	device->GetMouseState();
}

int Vigston::GetMouseX()
{
	return device->GetMouseX();
}

int Vigston::GetMouseY()
{
	return device->GetMouseY();
}