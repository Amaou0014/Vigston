#pragma once

#include "direct3d.h"

#include <map>

struct AnimationNum {
	unsigned int numU;
	unsigned int numV;
};

class Image
{
public:
	std::map<const char*, IDirect3DTexture9*> textureList;

	// �����_�[�X�e�[�g�̐ݒ�
	enum RENDERSTATE
	{
		RENDER_DEFAULT,		// �f�t�H���g(�s����)
		RENDER_ALPHATEST,	// ���e�X�g
		RENDER_HALFADD,		// �����Z����
		RENDER_ADD			// ���Z����
	};

	// �|���S�����_���
	struct Vertex {
		float x, y, z;// 3�������W
		float rhw;	// 2D�ϊ��ς݃t���O
		float u, v;	// UV���W
	};

	// FVF�i�_��Ȓ��_�\���̐錾�j�t���O
	static const DWORD SPRITE_FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;

	struct Sprite
	{
		// �X�v���C�g�ʒu
		D3DXVECTOR2 pos;
		// �X�v���C�g�T�C�Y
		int width;
		int height;
		// UV�̕�����
		unsigned int divU;
		unsigned int divV;
		// UV�̔ԍ�
		unsigned int numU;
		unsigned int numV;
		// ��]�l�i���W�A���j
		float rotate;
	};

	std::map<const char*, Sprite*> spriteList;

	//// �X�v���C�g�ʒu
	//D3DXVECTOR2 pos;
	//// �X�v���C�g�T�C�Y
	//int width;
	//int height;
	//// UV�̕�����
	//unsigned int divU;
	//unsigned int divV;
	//// UV�̔ԍ�
	//unsigned int numU;
	//unsigned int numV;
	//// ��]�l�i���W�A���j
	//float rotate;

	// �R���X�g���N�^
	Image();
	// �f�X�g���N�^
	~Image();
	// �摜�f�[�^�ǂݍ���
	bool Load(const char* keyname, IDirect3DDevice9* pDevice3D, TCHAR* FileName);

	void Set_Pos(const char* keyname, float x, float y);
	void Set_Width(const char* keyname, int Width, int Height);
	void Set_Rotate(const char* keyname, float Rotate);

	void SetRenderState(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState);

	float Get_PosX(const char* keyname);
	float Get_PosY(const char* keyname);
	int Get_Width(const char* keyname);
	int Get_Height(const char* keyname);
	float Get_Rotate(const char* keyname);

	void Move_Pos(const char* keyname, float x, float y);
	void Move_Rotate(const char* keyname, float Rotate);

	void Set_Divide(const char* keyname, unsigned int DivU, unsigned int DivV);
	void Set_UVNum(const char* keyname, unsigned int NumU, unsigned int NumV);
	void Draw(const char* keyname, IDirect3DDevice9* pDevice3D, bool isTurn = false);
};

// �X�v���C�g�̓����蔻��
bool IsHit(const char* keyname);