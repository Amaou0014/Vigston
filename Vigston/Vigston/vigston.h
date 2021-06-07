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

	Texture tex_slime;

	Sprite sprite[2];


	const TCHAR* WC_BASIC = _T("BASIC_WINDOW");
	WNDCLASSEX wcex;

	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;

	HWND hWnd;

	Vigston();
	~Vigston();

	// ‰Šú‰»
	void Init(HWND hWnd);
	// Update‚Ì‘O‚Éˆê‰ñ‚¾‚¯ŒÄ‚Î‚ê‚é
	void Start();
	// –ˆƒtƒŒ[ƒ€ŒÄ‚Î‚ê‚é
	virtual void Update();
};