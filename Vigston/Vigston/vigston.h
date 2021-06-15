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

	Wave wave_retoro1;
	SoundBuffer sb_retolo1;

	Wave wave_retoro2;
	SoundBuffer sb_retolo2;

	bool flag = false;

	const TCHAR* WC_BASIC = _T("BASIC_WINDOW");
	WNDCLASSEX wcex;

	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;

	HWND hWnd;

	DWORD backColor;

	Vigston();
	~Vigston();

	//���̊֐��̒��ɏ����������Ă�
	/////////////////////////////////

	// ������
	void Init(HWND hWnd);
	// Update�̑O�Ɉ�񂾂��Ă΂��
	void Start();
	// ���t���[���Ă΂��
	void Update();

	/////////////////////////////////

	// �w�i�F�Z�b�g(�\�Z�i��)
	void Set_BackColor(unsigned int color);

	// ��ʃ��Z�b�g
	void Clear_Screen();

	// �����_�����O�J�n
	bool Begine_Scene();
	// �����_�����O�I��
	bool End_Scene();

	// �摜�ǂݍ���
	bool Load_Texture(TCHAR* name, Texture* texture);

	// �����ǂݍ���
	bool Load_Sound(TCHAR* name, Wave* wave, SoundBuffer* sb);
	// �����Đ�
	void Play_Sound(bool isLoop, SoundBuffer* sb);
	// ���ʕύX
	void Set_Volume(long _volume, SoundBuffer* sb);
	// ���ʎ擾
	long Get_Volume(SoundBuffer* sb);

	// �`��ʒu�Z�b�g
	void Set_Sprite(float x, float y, int width, int height, float rotate, Sprite* sprite);
	// �`��ʒu�𓮂���
	void Move_Sprite(float x, float y, float rotate, Sprite* sprite);
	// �`�悷��
	void Draw(Texture* texture, Sprite* sprite);
};