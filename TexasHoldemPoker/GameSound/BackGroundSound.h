#pragma once
#include "Sound.h"
class BackGroundSound :
	public Sound
{
private:
	SoundState m_State;
public:
	BackGroundSound();
	BackGroundSound(const BackGroundSound& other);
	~BackGroundSound();

	bool InitializeBasic(const WCHAR* filepath, AudioEngine* engine, GameOption* option); // Header에 직접 웨이브 파일과 데이터를 읽는 방식
	bool Update();
	bool Play();
	bool Pause();
	bool Stop();
	bool Restart();

	bool Release();
};

