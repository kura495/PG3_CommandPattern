#pragma once
#include "DirectXCommon.h"
#include "Math_Structs.h"
#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include <x3daudio.h>
#include <cassert>
#include <fstream>
#include <map>

struct ChunkHeader {
	char id[4];//チャンクID
	int32_t size;//チャンクサイズ
};
struct RiffHeader {
	ChunkHeader chunk;//"RIFF"
	char type[4];//"WAVE"
};
struct FormatChunk {
	ChunkHeader chunk;//"fmt "
	WAVEFORMATEX fmt;//フォーマット
};
struct SoundData {
	//波形フォーマット
	WAVEFORMATEX wfex;
	//バッファの先頭
	BYTE* pBuffer;
	//バッファのサイズ
	unsigned int bufferSize;
};
class Audio {
public:
	static Audio* GetInstance();
	void Initialize();
	
	void Release();
	uint32_t LoadAudio(const char* filename);
	void Play(int AudioInDex, float AudioVolume, int pan);
	void SoundUnload(uint32_t Index);
private:
	Audio() = default;
	~Audio() = default;
	Audio(const Audio& obj) = delete;
	Audio& operator=(const Audio& obj) = delete;

	float left = 0;
	float right = 0;
	static const int kMaxAudio = 8;
	HRESULT hr;
	Microsoft::WRL::ComPtr<IXAudio2> XAudioInterface = nullptr;
	IXAudio2MasteringVoice* pMasteringVoice = nullptr;
	//ソースボイス
	IXAudio2SourceVoice* pSourceVoice[kMaxAudio];
	bool IsusedAudioIndex[kMaxAudio];
	//生音声データ
	//再生中にぶっ飛ばすとバグるぜ！！！
	std::map<uint32_t, SoundData> soundData_;

	float outputMatrix[8];

	SoundData SoundLoadWave(const char* filename);
	
	void Log(const std::string& message);
};

