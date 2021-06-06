#include "directsound.h"


DirectSound::DirectSound()
{
	pDirectSound8 = NULL;
}

DirectSound::~DirectSound()
{
	if(pDirectSound8 != NULL)
		pDirectSound8->Release();
}

bool DirectSound::Create(HWND hWnd)
{
	// サウンドデバイス作成
	DirectSoundCreate8(NULL, &pDirectSound8, NULL);	
	// 協調レベルのセット（ここで音を鳴らすウィンドウを指定する必要がある）
	if (FAILED(pDirectSound8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
	{
		// 失敗
		return false;
	}

	return true;
}