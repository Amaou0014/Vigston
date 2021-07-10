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
	// �T�E���h�f�o�C�X�쐬
	DirectSoundCreate8(NULL, &pDirectSound8, NULL);
	// �������x���̃Z�b�g
	if (FAILED(pDirectSound8->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)))
	{
		// ���s
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
	// �o�C�i���ǂݍ��݃��[�h�ŊJ��
	FILE* fp;
	if (!(fp = ::_tfopen(filename, _T("rb"))))
		return false;

	char chunkId[5] = {};
	char tmp[5] = {};
	unsigned int chunkSize = 0;

	// RIFF�`�����N�ǂݍ���
	fread(chunkId, sizeof(char) * 4, 1, fp);
	fread(&chunkSize, sizeof(unsigned int), 1, fp);
	fread(tmp, sizeof(char) * 4, 1, fp);
	if (strcmp(chunkId, "RIFF") || strcmp(tmp, "WAVE")) {
		return false;	// Wave�t�@�C������Ȃ�
	}

	// �q�`�����N�ǂݍ���
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
			// �f�[�^�T�C�Y�m��
			wave->DataSize = chunkSize;
			wave->WaveData = new byte[chunkSize];
			// �f�[�^�ǂݍ���
			if (fread(wave->WaveData, sizeof(byte), chunkSize, fp) != chunkSize)
			{
				fclose(fp);
				return false;	// �t�@�C�������Ă���
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
	// �Z�J���_���o�b�t�@���X�g���
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
	DSBUFFERDESC	desc = {};			// �Z�J���_���o�b�t�@�쐬�p�ݒ�
	// �`�����l�����ł̕���A���m������1�`�����l���A�X�e���I��2�`�����l��
	if (wave->WaveFormat.nChannels == 1) {
		desc.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY |
			DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_STATIC;
		desc.guid3DAlgorithm = DS3DALG_NO_VIRTUALIZATION;
	}
	else {
		desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY |
			DSBCAPS_GETCURRENTPOSITION2 | DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_CTRLPAN | DSBCAPS_STATIC;
		// | DSBCAPS_CTRLFX;	�G�t�F�N�g��ǉ������ Duplicate �ł��Ȃ�
		desc.guid3DAlgorithm = GUID_NULL;
	}
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwBufferBytes = wave->DataSize;			// ���f�[�^�T�C�Y�w��
	desc.lpwfxFormat = &wave->WaveFormat;		// �t�H�[�}�b�g�w��

	IDirectSoundBuffer* pPrimaryBuffer = NULL;	// �v���C�}���o�b�t�@
	// �v���C�}���o�b�t�@�쐬
	pDirectSound8->CreateSoundBuffer(&desc, &pPrimaryBuffer, NULL);
	// �v���C�}���o�b�t�@����Z�J���_���o�b�t�@�쐬
	pPrimaryBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&bufferList[keyname]);
	pPrimaryBuffer->Release();	// �Z�J���_���o�b�t�@���쐬�ł���΁A�v���C�}���o�b�t�@�͔j�����Ă��܂�Ȃ�

	unsigned char* block1 = NULL;
	unsigned char* block2 = NULL;
	unsigned long blockSize1 = 0;
	unsigned long blockSize2 = 0;
	// �Z�J���_���o�b�t�@�����b�N���ăf�[�^��������
	bufferList[keyname]->Lock(0, wave->DataSize,
		(void**)&block1, &blockSize1, (void**)&block2, &blockSize2, DSBLOCK_ENTIREBUFFER);
	// �Z�J���_���o�b�t�@�ɉ��f�[�^�R�s�[
	memcpy(block1, wave->WaveData, wave->DataSize);

	// �Z�J���_���o�b�t�@���b�N����
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