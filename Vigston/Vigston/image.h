#pragma once

#include "direct3d.h"

class Image
{
public:
	IDirect3DTexture9* pTexture;
	// �R���X�g���N�^
	Image();
	// �f�X�g���N�^
	~Image();
	// �摜�f�[�^�ǂݍ���
	bool Load(IDirect3DDevice9* pDevice3D, TCHAR* FileName);
};