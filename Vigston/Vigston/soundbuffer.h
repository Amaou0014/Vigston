#pragma once 

#include "directsound.h"

class SoundBuffer
{
public:
	IDirectSoundBuffer8*	pSecondaryBuffer;	// セカンダリバッファ
	
	SoundBuffer();
	~SoundBuffer();

	bool Create(IDirectSound8*	pDirectSound8,WAVEFORMATEX& WaveFormat,byte* WaveData,int DataSize);

	// サウンド再生
	void Play(bool isLoop);
	// サウンド止める
	void Stop();
	// 音量変更
	void ChangeVolume(long _volume);
	long GetVolume(long _volume);
};
