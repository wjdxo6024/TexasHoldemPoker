#include "EffectSound.h"

EffectSound::EffectSound()
{

}

EffectSound::EffectSound(const EffectSound& other)
{

}

EffectSound::~EffectSound()
{
	this->Release();
}

bool EffectSound::InitializeBasic(const WCHAR* filepath, AudioEngine* engine, GameOption* option)
{
	if (!Sound::InitializeBasic(filepath, engine, option))
		return false;

	Update();
	return true;
}

bool EffectSound::Update()
{
	Sound::m_SourceVoice->SetVolume(extOption->GetEffectSoundVolume());
	return true;
}

bool EffectSound::Play()
{
	Sound::m_SourceVoice->SetVolume(Sound::extOption->GetEffectSoundVolume());
	return Sound::Play();
}

bool EffectSound::Release()
{
	return true;
}