#pragma once

#define DIRECTSOUND_VERSION 0x800	// DirectSound�̃o�[�W����

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "d3dxof.lib")
#pragma comment(lib, "dxguid.lib")

#include <map>
#include <comdef.h>
#include <dsound.h>
#include <tchar.h>

class Sound
{
public:
	struct Wave
	{
		WAVEFORMATEX		WaveFormat;	// Wave�t�H�[�}�b�g
		byte* WaveData;	// ���̐��f�[�^
		int					DataSize;	// �f�[�^�T�C�Y
	};

	IDirectSound8* pDirectSound8; // DirectSound�f�o�C�X

	std::map<const char*, IDirectSoundBuffer8*> bufferList;  // �Z�J���_���o�b�t�@���X�g

	Wave* wave;  // Wave�t�@�C���̃f�[�^


	Sound();
	~Sound();

	// �T�E���h�f�o�C�X������
	void Init_Device();
	// �T�E���h�f�o�C�X���
	void Release_Device();
	// �T�E���h�f�o�C�X�쐬
	bool Create_Device(HWND hWnd);

	// Wave������
	void Init_Wave();
	// Wave���
	void Release_Wave();
	// Wave�t�@�C���ǂݍ���
	bool Load_Wave(const char* keyname, TCHAR* filename);

	// �Z�J���_���o�b�t�@������
	void Init_Buffer();
	// �Z�J���_���o�b�t�@���
	void Release_Buffer();
	// �Z�J���_���o�b�t�@�쐬
	bool Create_Buffer(const char* keyname);
	// �T�E���h�Đ�
	void Play(const char* keyname, bool isLoop);
	// �T�E���h�~�߂�
	void Stop(const char* keyname);
	// ���ʕύX
	void SetVolume(const char* keyname, long _volume);
	// ���ʎ擾
	long GetVolume(const char* keyname);
};