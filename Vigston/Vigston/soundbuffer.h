#pragma once 

#include "directsound.h"

class SoundBuffer
{
public:
	IDirectSoundBuffer8*	pSecondaryBuffer;	// �Z�J���_���o�b�t�@
	
	SoundBuffer();
	~SoundBuffer();

	bool Create(IDirectSound8*	pDirectSound8,WAVEFORMATEX& WaveFormat,byte* WaveData,int DataSize);

	// �T�E���h�Đ�
	void Play(bool isLoop);
	// �T�E���h�~�߂�
	void Stop();
	// ���ʕύX
	void ChangeVolume(long _volume);
	long GetVolume(long _volume);
};
