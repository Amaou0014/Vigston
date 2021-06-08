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

	Sprite sprite;

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

	// �`��ʒu�Z�b�g
	void SetSprite(float x, float y, int width, int height, float rotate, Sprite* sprite);
};