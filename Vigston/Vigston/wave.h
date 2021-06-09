#pragma once

#include "directsound.h"


class Wave{
public:
	WAVEFORMATEX		WaveFormat;	// Wave�t�H�[�}�b�g
	byte*				WaveData;	// ���̐��f�[�^
	int					DataSize;	// �f�[�^�T�C�Y

	// �R���X�g���N�^
	Wave();
	// �f�X�g���N�^
	~Wave();

	// Wav�t�@�C���ǂݍ���
	bool Load(TCHAR* FileName);
};
