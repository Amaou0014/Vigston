#pragma once

#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "text.h"
#include "directsound.h"
#include "wave.h"
#include "soundbuffer.h"


class Vigston
{
public:
	Direct3D	direct3d;
	DirectSound	directsound;

	Texture texture;

	Texture tex_slime;

	//Sprite sprite[2];

	Sprite sprite;
	Sprite sprite1;

	const TCHAR* WC_BASIC = _T("BASIC_WINDOW");
	WNDCLASSEX wcex;

	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;

	HWND hWnd;

	Vigston();
	~Vigston();

	// ������
	void Init(HWND hWnd);
	// Update�̑O�Ɉ�񂾂��Ă΂��
	void Start();
	// ���t���[���Ă΂��
	void Update();

	bool LoadTexture(TCHAR* name, Texture* texture);
};