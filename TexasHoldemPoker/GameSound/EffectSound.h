#pragma once
#include "Sound.h"
class EffectSound :
	public Sound
{
public:
	EffectSound();
	EffectSound(const EffectSound& other);
	~EffectSound();

	bool InitializeBasic(const WCHAR* filepath, AudioEngine* engine, GameOption* option); // Header�� ���� ���̺� ���ϰ� �����͸� �д� ���
	bool Update();
	bool Play();
	bool Release();
};

