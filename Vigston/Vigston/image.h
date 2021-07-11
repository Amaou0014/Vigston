#pragma once

#include "direct3d.h"

struct AnimationNum {
	unsigned int numU;
	unsigned int numV;
};

class Image
{
public:
	IDirect3DTexture9* pTexture;

	// �����_�[�X�e�[�g�̐ݒ�
	enum RENDERSTATE
	{
		RENDER_DEFAULT,		// �f�t�H���g(�s����)
		RENDER_ALPHATEST	// ���e�X�g
	};
	// �|���S�����_���
	struct Vertex {
		float x, y, z;// 3�������W
		float rhw;	// 2D�ϊ��ς݃t���O
		float u, v;	// UV���W
	};
	// FVF�i�_��Ȓ��_�\���̐錾�j�t���O
	static const DWORD SPRITE_FVF = D3DFVF_XYZRHW | D3DFVF_TEX1;

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

	// �R���X�g���N�^
	Image();
	// �f�X�g���N�^
	~Image();
	// �摜�f�[�^�ǂݍ���
	bool Load(IDirect3DDevice9* pDevice3D, TCHAR* FileName);

	void Set_Pos(float x, float y);
	void Set_Width(int Width, int Height);
	void Set_Rotate(float Rotate);

	void SetRenderState(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState);

	float Get_PosX();
	float Get_PosY();
	int Get_Width();
	int Get_Height();
	float Get_Rotate();

	void Move_Pos(float x, float y);
	void Move_Rotate(float Rotate);

	void Set_Divide(unsigned int DivU, unsigned int DivV);
	void Set_UVNum(unsigned int NumU, unsigned int NumV);
	void Draw(IDirect3DDevice9* pDevice3D, IDirect3DTexture9* pTexture, bool isTurn = false);
};

// �X�v���C�g�̓����蔻��
bool IsHit(const Image& image1, const Image& image2);