#pragma once
#include "Sound.h"
class EffectSound :
	public Sound
{
public:
	EffectSound();
	EffectSound(const EffectSound& other);
	~EffectSound();

	bool InitializeBasic(const WCHAR* filepath, AudioEngine* engine, GameOption* option); // Header에 직접 웨이브 파일과 데이터를 읽는 방식
	bool Update();
	bool Play();
	bool Release();
};

