#define _CRT_SECURE_NO_WARNINGS

#include "sound.h"

Sound::Sound()
{
	Init_SoundDevice();
	Init_Wave();
	Init_Buffer();
}

Sound::~Sound()
{
	Release_SoundDevice();
	Release_Wave();
	Release_Buffer();
}

void Sound::Init_SoundDevice()
{
	pDirectSound8 = NULL;
}

void Sound::Release_SoundDevice()
{
	if (pDirectSound8 != NULL)
	{
		pDirectSound8->Release();
	}
}

bool Sound::Create_SoundDevice(HWND hWnd)
{
	// サウンドデバイス作成
	DirectSoundCreate8(NULL, &pDirectSound8, NULL);
	// 協調レベルのセット
	if (FAILED(pDirectSound8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
	{
		// 失敗
		return false;
	}

	return true;
}

void Sound::Init_Wave()
{
	wave = new Wave();
	memset(&wave->WaveFormat,0,sizeof(WAVEFORMATEX));
	wave->WaveData = NULL;
	wave->DataSize = 0;
}

void Sound::Release_Wave()
{
	if (wave->WaveData != NULL)
	{
		delete[] wave->WaveData;
	}

	delete wave;
}

bool Sound::Load_Wave(TCHAR* filename)
{
	// バイナリ読み込みモードで開く
	FILE* fp;
	if (!(fp = ::_tfopen(filename, _T("rb"))))
		return false;

	char chunkId[5] = {};
	char tmp[5] = {};
	unsigned int chunkSize = 0;

	// RIFFチャンク読み込み
	fread(chunkId, sizeof(char) * 4, 1, fp);
	fread(&chunkSize, sizeof(unsigned int), 1, fp);
	fread(tmp, sizeof(char) * 4, 1, fp);
	if (strcmp(chunkId, "RIFF") || strcmp(tmp, "WAVE")) {
		return false;	// Waveファイルじゃない
	}

	// 子チャンク読み込み
	bool fmtchunk = false;
	bool datachunk = false;
	while (true)
	{
		fread(chunkId, sizeof(char) * 4, 1, fp);
		fread(&chunkSize, sizeof(unsigned int), 1, fp);
		if (!strcmp(chunkId, "fmt "))
		{
			if (chunkSize >= sizeof(WAVEFORMATEX))
			{
				fread(&wave->WaveFormat, sizeof(WAVEFORMATEX), 1, fp);
				int diff = chunkSize - sizeof(WAVEFORMATEX);
				fseek(fp, diff, SEEK_CUR);
			}
			else
			{
				memset(&wave->WaveFormat, 0, sizeof(WAVEFORMATEX));
				fread(&wave->WaveFormat, chunkSize, 1, fp);
			}
			fmtchunk = true;
		}
		else if (!strcmp(chunkId, "data"))
		{
			// データサイズ確保
			wave->DataSize = chunkSize;
			wave->WaveData = new byte[chunkSize];
			// データ読み込み
			if (fread(wave->WaveData, sizeof(byte), chunkSize, fp) != chunkSize)
			{
				fclose(fp);
				return false;	// ファイルが壊れている
			}
			datachunk = true;
		}
		else
		{
			fseek(fp, chunkSize, SEEK_CUR);
		}

		if (fmtchunk && datachunk)
			break;
	}

	fclose(fp);
	return true;
}

void Sound::Init_Buffer()
{
	if (!bufferList.empty())
	{
		bufferList.clear();
	}
}

void Sound::Release_Buffer()
{
	// セカンダリバッファリスト解放
	for (auto buf = bufferList.begin(); buf != bufferList.end(); buf++)
	{
		if (buf->second != nullptr)
		{
			buf->second->Stop();
			buf->second->Release();
			buf->second = nullptr;
		}
	}

	bufferList.clear();
}

bool Sound::Create_Buffer(const char* keyname)
{
	DSBUFFERDESC	desc = {};			// セカンダリバッファ作成用設定
	// チャンネル数での分岐、モノラルは1チャンネル、ステレオは2チャンネル
	if (wave->WaveFormat.nChannels == 1) {
		desc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY |
			DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_STATIC;
		desc.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;
	}
	else {
		desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY |
			DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_CTRLPAN | DSBCAPS_STATIC;
		// | DSBCAPS_CTRLFX;	エフェクトを追加すると Duplicate できない
		desc.guid3DAlgorithm = GUID_NULL;
	}
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwBufferBytes = wave->DataSize;			// 音データサイズ指定
	desc.lpwfxFormat = &wave->WaveFormat;		// フォーマット指定

	IDirectSoundBuffer* pPrimaryBuffer = NULL;	// プライマリバッファ
	// プライマリバッファ作成
	pDirectSound8->CreateSoundBuffer(&desc, &pPrimaryBuffer, NULL);
	// プライマリバッファからセカンダリバッファ作成
	pPrimaryBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&bufferList[keyname]);
	pPrimaryBuffer->Release();	// セカンダリバッファが作成できれば、プライマリバッファは破棄してかまわない

	unsigned char* block1 = NULL;
	unsigned char* block2 = NULL;
	unsigned long blockSize1 = 0;
	unsigned long blockSize2 = 0;
	// セカンダリバッファをロックしてデータ書き込み
	bufferList[keyname]->Lock(0, wave->DataSize,
		(void**)&block1, &blockSize1, (void**)&block2, &blockSize2, DSBLOCK_ENTIREBUFFER);
	// セカンダリバッファに音データコピー
	memcpy(block1, wave->WaveData, wave->DataSize);

	// セカンダリバッファロック解除
	bufferList[keyname]->Unlock(block1, blockSize1, block2, 0);

	return true;
}

void Sound::Play(const char* keyname, bool isLoop)
{
	if (bufferList[keyname] != NULL) {
		bufferList[keyname]->Play(0, 0, (DWORD)isLoop);
	}
}

void Sound::Stop(const char* keyname)
{
	if (bufferList[keyname] != NULL)
	{
		bufferList[keyname]->Stop();
	}
}

void Sound::SetVolume(const char* keyname, long _volume)
{
	if (bufferList[keyname] != NULL)
	{
		bufferList[keyname]->SetVolume((LONG)_volume);
	}
}

long Sound::GetVolume(const char* keyname)
{
	long _volume = 0;
	if (bufferList[keyname] != NULL)
	{
		bufferList[keyname]->GetVolume((LPLONG)_volume);
		return _volume;
	}
}