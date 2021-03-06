#pragma once

#define DIRECTSOUND_VERSION 0x800	// DirectSoundのバージョン

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "d3dxof.lib")
#pragma comment(lib, "dxguid.lib")

#include <map>
#include <comdef.h>
#include <dsound.h>
#include <tchar.h>

// サウンドクラス
class Sound
{
public:
	// Waveデータの構造体
	struct Wave
	{
		WAVEFORMATEX		WaveFormat;	// Waveフォーマット
		byte*				WaveData;	// 音の生データ
		int					DataSize;	// データサイズ
	};

	IDirectSound8* pDirectSound8; // DirectSoundデバイス

	std::map<const char*, IDirectSoundBuffer8*> bufferList;  // セカンダリバッファリスト

	Wave* wave;  // Waveファイルのデータ


	// コンストラクタ
	Sound();
	// デストラクタ
	~Sound();

	// サウンドデバイス初期化
	void Init_SoundDevice();
	// サウンドデバイス解放
	void Release_SoundDevice();
	// サウンドデバイス作成
	bool Create_SoundDevice(HWND hwnd);

	// Wave初期化
	void Init_Wave();
	// Wave解放
	void Release_Wave();
	// Waveファイル読み込み
	bool Load_Wave(TCHAR* filename);

	// セカンダリバッファ初期化
	void Init_Buffer();
	// セカンダリバッファ解放
	void Release_Buffer();
	// セカンダリバッファ作成
	bool Create_Buffer(const char* keyname);
	// サウンド再生
	void Play(const char* keyname, bool isLoop);
	// サウンド止める
	void Stop(const char* keyname);
	// 音量変更
	void SetVolume(const char* keyname, long _volume);
	// 音量取得
	long GetVolume(const char* keyname);
};