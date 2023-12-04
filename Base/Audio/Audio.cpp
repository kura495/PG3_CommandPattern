#include"Audio.h"

Audio* Audio::GetInstance()
{
	static Audio instance;
	return &instance;
}
void Audio::Initialize() {
	hr=XAudio2Create(&XAudioInterface,0,XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(hr));
	hr = XAudioInterface->CreateMasteringVoice(&pMasteringVoice);
	assert(SUCCEEDED(hr));
	for (int i = 0; i < kMaxAudio; i++) {
		pSourceVoice[i] = nullptr;
		IsusedAudioIndex[i] = false;
	}
		DWORD dwChannelMask;
	pMasteringVoice->GetChannelMask(&dwChannelMask);
	for (int i = 0; i < 8; i++) outputMatrix[i] = 0;
	 //pan of -1.0 indicates all left speaker, 
 //1.0 is all right speaker, 0.0 is split between left and right
	switch (dwChannelMask)
	{
	case SPEAKER_MONO:
		outputMatrix[0] = 1.0;
		break;
	case SPEAKER_STEREO:
	case SPEAKER_2POINT1:
	case SPEAKER_SURROUND:
		outputMatrix[0] = left;
		outputMatrix[1] = right;
		break;
	case SPEAKER_QUAD:
		outputMatrix[0] = outputMatrix[2] = left;
		outputMatrix[1] = outputMatrix[3] = right;
		break;
	case SPEAKER_4POINT1:
		outputMatrix[0] = outputMatrix[3] = left;
		outputMatrix[1] = outputMatrix[4] = right;
		break;
	case SPEAKER_5POINT1:
	case SPEAKER_7POINT1:
	case SPEAKER_5POINT1_SURROUND:
		outputMatrix[0] = outputMatrix[4] = left;
		outputMatrix[1] = outputMatrix[5] = right;
		break;
	case SPEAKER_7POINT1_SURROUND:
		outputMatrix[0] = outputMatrix[4] = outputMatrix[6] = left;
		outputMatrix[1] = outputMatrix[5] = outputMatrix[7] = right;
		break;
	}
	// Assuming pVoice sends to pMasteringVoice
}

uint32_t Audio::LoadAudio(const char* filename) {
#pragma region Index
	uint32_t AudioIndex = kMaxAudio + 1;
	    for (int i = 0; i < kMaxAudio; ++i) {
		if (IsusedAudioIndex[i] == false) {
			AudioIndex = i;
			IsusedAudioIndex[i] = true;
			break;
		}
	    }
	    if (AudioIndex < 0) {
		// 0より少ない
		assert(false);
	    }
	    if (kMaxAudio < AudioIndex) {
		// MaxSpriteより多い
		assert(false);
	    }
#pragma endregion 位置決め
		soundData_[AudioIndex] = SoundLoadWave(filename);
		if (FAILED(XAudioInterface->CreateSourceVoice(&pSourceVoice[AudioIndex], &soundData_[AudioIndex].wfex))) {
			SoundUnload(AudioIndex);
			assert(false);
		}
	    XAUDIO2_BUFFER buffer{};
	    buffer.pAudioData = soundData_[AudioIndex].pBuffer;
	    buffer.Flags = XAUDIO2_END_OF_STREAM;
	    buffer.AudioBytes = soundData_[AudioIndex].bufferSize;
	    buffer.LoopBegin = 0;
	    buffer.LoopLength = 0;
	    buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

	    pSourceVoice[AudioIndex]->SubmitSourceBuffer(&buffer);

		return AudioIndex;
}

void Audio::Release() {
	
	for (int i=0;i<kMaxAudio;i++) {
		if (pSourceVoice[i]) {
		pSourceVoice[i]->DestroyVoice();
		}
	}
	if (pMasteringVoice) {
		pMasteringVoice->DestroyVoice();
		pMasteringVoice = nullptr;
	}
	if (XAudioInterface) {
		XAudioInterface->Release();
		XAudioInterface = nullptr;
	}
	soundData_.clear();
	CoUninitialize();
}

void Audio::Play(int AudioIndex,float AudioVolume,int pan) {
	// pan of -1.0 indicates all left speaker, 
// 1.0 is all right speaker, 0.0 is split between left and right
	right = 0;
	left=0;
	if (pan >= 1) {
		right = 1;
	}
	else if (pan < 0) {
		left = 1;
	}
	else if(pan == 0) {
		right = 1;
		left = 1;
	}
	outputMatrix[0] =right;
	outputMatrix[2] =left ;
	int InChannels = 2;
	int OutChannels = 4;
	pSourceVoice[AudioIndex]->SetOutputMatrix(NULL, InChannels, OutChannels, outputMatrix);
	pSourceVoice[AudioIndex]->SetVolume(AudioVolume);
	pSourceVoice[AudioIndex]->Start(0);
}

SoundData Audio::SoundLoadWave(const char* filename)
{
	//ファイル入力ストリームのインスタンス
	std::ifstream file;
	//.wavファイルをバイナリモードで開く
	file.open(filename,std::ios_base::binary);
	//ファイルオープン失敗を検出
	assert(file.is_open());
	//RIFFチャンク読み込み
	RiffHeader riff;
	//チャンクがRIFFかチェック
	file.read((char*)&riff, sizeof(riff));
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}
	//ファイルタイプがWAVEかチェック
	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}
	//formatチャンク読み込み
	FormatChunk format = {};
	//チャンクヘッダーの確認
	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}
	//チャンク本体の読み込み
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);

	//Dataチャンク読み込み
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	if (strncmp(data.id, "bext", 4) == 0) {
		//JUNKチャンクの終わりまで進める
		file.seekg(data.size, std::ios_base::cur);
		//再読み込み
		file.read((char*)&data, sizeof(data));
	}
	//JUNKチャンクの場合
	if (strncmp(data.id, "junk", 4) == 0) {
		//JUNKチャンクの終わりまで進める
		file.seekg(data.size, std::ios_base::cur);
		//再読み込み
		file.read((char*)&data, sizeof(data));
	}
	if (strncmp(data.id, "data", 4) != 0) {
		assert(0);
	}
	//Dataチャンクの波形データを読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);

	file.close();

	SoundData soundData = {};

	soundData.wfex = format.fmt;
	soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	soundData.bufferSize = data.size;

	return soundData;
}

void Audio::SoundUnload(uint32_t Index)
{
	auto it = soundData_.find(Index);
	if (it != soundData_.end()) {
		delete[] soundData_[Index].pBuffer;
		soundData_[Index].pBuffer = 0;
		soundData_[Index].bufferSize = 0;
		soundData_[Index].wfex = {};
	}
}

void Audio::Log(const std::string& message) { OutputDebugStringA(message.c_str()); }