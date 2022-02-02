#pragma once
#include <xaudio2.h>
#include "../GameOption/GameOption.h"
// XAudio Engine
// Sound 클래스를 받고 실행한다.

class AudioEngine
{
private:
	IXAudio2* m_XAudio2;
	IXAudio2MasteringVoice* m_MasterVoice;
	GameOption* extGameOption;
public:
	AudioEngine();
	AudioEngine(const AudioEngine& other);
	~AudioEngine();

	bool Initialize();
	bool Initialize(GameOption* option);
	bool Update();
	bool Release();

	bool AllPlayingStart();
	bool AllPlayingStop();
	bool AllPlayingPause();
	bool AllPlayingRestart();

	IXAudio2* GetXAudio2();
	float GetEffectVolume();
	void SetEffectVolume(float volume);
	float GetBackGroundVolume();
	void SetBackGroundVolume(float volume);
};

