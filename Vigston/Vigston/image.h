#pragma once

#include "direct3d.h"

#include <map>

// �ǂݍ��񂾉摜�̃i���o�[
struct AnimationNum {
	unsigned int numU;
	unsigned int numV;
};

// �摜�`��N���X
class Image
{
public:
	// �e�N�X�`�����X�g
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

	// �X�v���C�g�`��N���X
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

	// �X�v���C�g�N���X�̃��X�g
	std::map<const char*, Sprite*> spriteList;

	// �R���X�g���N�^
	Image();
	// �f�X�g���N�^
	~Image();

	// �摜�f�[�^�ǂݍ���
	bool Load(const char* keyname, IDirect3DDevice9* pDevice3D, TCHAR* FileName);
	// �摜�`��̍��W�Z�b�g
	void Set_Pos(const char* keyname, float x, float y);
	// �摜�`��̃T�C�Y�Z�b�g
	void Set_Size(const char* keyname, int Width, int Height);
	// �摜�`��̊p�x�Z�b�g
	void Set_Rotate(const char* keyname, float Rotate);

	// �摜�̓��ߔ͈͂𓧉�
	void SetRenderState(IDirect3DDevice9* pD3DDevice, RENDERSTATE RenderState);

	// �摜�`��̍��WX�擾
	float Get_PosX(const char* keyname);
	// �摜�`��̍��WY�擾
	float Get_PosY(const char* keyname);
	// �摜�`��̉����擾
	int Get_Width(const char* keyname);
	// �摜�`��̏c���擾
	int Get_Height(const char* keyname);
	// �摜�`��̊p�x�擾
	float Get_Rotate(const char* keyname);

	// �摜�`��̍��W�ύX
	void Move_Pos(const char* keyname, float x, float y);
	// �摜�`��̊p�x�ύX
	void Move_Rotate(const char* keyname, float Rotate);

	// �摜�𕪊����ĕۑ� ���}�b�v�`�b�v�ȂǂɎg��
	void Set_Divide(const char* keyname, unsigned int DivU, unsigned int DivV);
	// �摜�𕪊����ĕۑ������摜����ׂ�
	void Set_UVNum(const char* keyname, unsigned int NumU, unsigned int NumV);
	// �w�肳�ꂽ�L�[�ŕۑ�����Ă���摜��`��
	void Draw(const char* keyname, IDirect3DDevice9* pDevice3D, bool isTurn = false);
};

// �X�v���C�g�̓����蔻��
bool IsHit(const char* keyname);