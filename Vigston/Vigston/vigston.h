#pragma once

#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "text.h"
#include "sound.h"
#include "device.h"
#include "window.h"


class Vigston
{
public:
	Direct3D	direct3d;
	Sound* sound;

	Window window;

	MSG msg = {};

	Device device;

	bool flag = false;

	DWORD backColor;

	Vigston();
	~Vigston();

	//���̊֐��̒��ɏ����������Ă�
	/////////////////////////////////

	// ������
	void Init(HINSTANCE hInstance);

	/////////////////////////////////

	// �E�B���h�E�Z�b�g
	void Set_Window(const TCHAR* name, const HINSTANCE hInst);
	// �E�B���h�E���W�Z�b�g
	void Set_Window_Pos(int x, int y);
	// �E�B���h�E���W�Z�b�g
	void Set_Window_Size(int w, int h);
	// �E�B���h�E�쐬
	void Create_Window(LPCTSTR name, DWORD dwStyle, HWND hWndParent, HMENU hMenu);
	// ���b�Z�[�W���[�v
	bool GameQuit();
	// ���b�Z�[�W���[�v
	bool ProcessMessage();
	// �w�i�F�Z�b�g(�\�Z�i��)
	void Set_BackColor(unsigned int color);

	// ��ʃ��Z�b�g
	void Clear_Screen();

	// �����_�����O�J�n
	bool Begine_Scene();
	// �����_�����O�I��
	bool End_Scene();
	// �`�攽�f
	void ScreenFlip();

	// �摜�ǂݍ���
	bool Load_Texture(TCHAR* name, Texture* texture);

	// �����ǂݍ���
	bool Load_Sound(const char* keyname, TCHAR* name);
	// �����Đ�
	void Play_Sound(const char* keyname, bool isLoop);
	// ���ʕύX
	void Set_Volume(const char* keyname, long _volume);
	// ���ʎ擾
	long Get_Volume(const char* keyname);

	// �t�H���g�쐬
	bool Create_Font(int size, Text* text);
	// �t�H���g�`��
	void Draw_Font(int x, int y, DWORD color, Text* text, const TCHAR* str...);

	// �`��ʒu�Z�b�g
	void Set_Sprite(float x, float y, int width, int height, float rotate, Sprite* sprite);
	// �`��ʒu�𓮂���
	void Move_Sprite(float x, float y, float rotate, Sprite* sprite);
	// �`�悷��
	void Draw_Image(Texture* texture, Sprite* sprite);

	// �L�[���擾
	void GetKeyState();
	// �L�[�����͂���Ă��邩
	bool GetKey(unsigned char keycode);
	// �L�[���������u��
	bool PushKey(unsigned char keycode);
	// �L�[�𗣂����u��
	bool ReleaseKey(unsigned char keycode);

	// �}�E�X���擾
	void GetMouseState();
	// �}�E�XX���W�擾
	int GetMouseX();
	// �}�E�XY���W�擾
	int GetMouseY();
};