#pragma once

#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "text.h"
#include "directsound.h"
#include "wave.h"
#include "soundbuffer.h"
#include "keyboard.h"


class Vigston
{
public:
	Direct3D	direct3d;
	DirectSound	directsound;

	Texture texture;
	Sprite sprite;
	Keyboard keyboard;

	Wave wave_retoro1;
	SoundBuffer sb_retolo1;

	bool flag = false;

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

	// �摜�ǂݍ���
	bool LoadTexture(TCHAR* name, Texture* texture);

	// �����ǂݍ���
	bool LoadSound(TCHAR* name, Wave* wave, SoundBuffer* sb);
	// ���ʕύX
	void ChangeVolume(long _volume, SoundBuffer* sb);

	// �`��ʒu�Z�b�g
	void SetSprite(float x, float y, int width, int height, float rotate, Sprite* sprite);
};