#pragma once

#include "direct3d.h"
#include "image.h"
#include "text.h"
#include "sound.h"
#include "device.h"
#include "window.h"


// ���C�u�����̊�{�N���X
// ���̃N���X���̃��\�b�h���g���Ă��炤
class Vigston
{
public:
	//�e�N���X�I�u�W�F�N�g�|�C���^
	Direct3D*	direct3d;
	Sound*		sound;
	Image*		image;
	Text*		text;
	Device*		device;
	Window*		window;

	// �E�B���h�E�̃��b�Z�[�W���
	MSG msg = {};

	// �E�B���h�E�̔w�i�F
	DWORD backColor;

	// �R���X�g���N�^
	Vigston();
	// �f�X�g���N�^
	~Vigston();

	//���̊֐��̒��ɏ����������Ă�
	/////////////////////////////////

	// ������
	void Init();

	/////////////////////////////////

	// �E�B���h�E�Z�b�g
	void Set_Window(const TCHAR* name);
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
	bool Load_Image(const char* keyname, TCHAR* name, float x, float y, int width, int height, float rotate);
	// �摜�𕪊����ēǂݍ���
	bool LoadDiv_Image(const char* keyname, TCHAR* name, float x, float y, int width, int height, float rotate, unsigned int DivU, unsigned int DivV);
	// �`��ʒu�Z�b�g
	void Set_Image(const char* keyname, float x, float y, int width, int height, float rotate);
	// �`��ʒu�𓮂���
	void Move_Image(const char* keyname, float x, float y, float rotate);
	// �`����WX�擾
	float Get_Image_PosX(const char* keyname);
	// �`����WY�擾
	float Get_Image_PosY(const char* keyname);
	// �`�悷��
	void Draw_Image(const char* keyname, bool isTurn = false);

	// �����ǂݍ���
	bool Load_Sound(const char* keyname, TCHAR* name);
	// �����Đ�
	void Play_Sound(const char* keyname, bool isLoop);
	// ���ʕύX
	void Set_Volume(const char* keyname, long _volume);
	// ���ʎ擾
	long Get_Volume(const char* keyname);

	// �t�H���g�쐬
	bool Create_Font(int size);
	// �t�H���g�`��
	void Draw_Font(int x, int y, DWORD color, const TCHAR* str...);

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