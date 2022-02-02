#include "AudioEngine.h"

AudioEngine::AudioEngine()
{
	if (!this->Initialize())
	{
		MessageBox(NULL, L"Cannot Create AudioEngine.", L"Error", MB_OK);
	}
}

AudioEngine::AudioEngine(const AudioEngine& other)
{

}

AudioEngine::~AudioEngine()
{
	this->Release();
}

bool AudioEngine::Initialize()
{
	HRESULT hr;
	extGameOption = NULL;
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Initialize Ex.", L"Error", MB_OK);
#endif
		return false;
	}

	hr = XAudio2Create(&m_XAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create XAudio2.", L"Error", MB_OK);
#endif
		return false;
	}

	hr = m_XAudio2->CreateMasteringVoice(&m_MasterVoice);
	if (FAILED(hr))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create MasteringVoice.", L"Error", MB_OK);
#endif
		return false;
	}

	return true;
}

bool AudioEngine::Initialize(GameOption* option)
{
	HRESULT hr;
	extGameOption = option;
	hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (FAILED(hr))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Initialize Ex.", L"Error", MB_OK);
#endif
		return false;
	}

	hr = XAudio2Create(&m_XAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	if (FAILED(hr))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create XAudio2.", L"Error", MB_OK);
#endif
		return false;
	}

	hr = m_XAudio2->CreateMasteringVoice(&m_MasterVoice);
	if (FAILED(hr))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create MasteringVoice.", L"Error", MB_OK);
#endif
		return false;
	}

	return true;
}

bool AudioEngine::Update()
{
	return true;
}

bool AudioEngine::Release()
{
	if (m_MasterVoice != NULL)
	{
		m_MasterVoice->DestroyVoice();
		m_MasterVoice = 0;
	}

	if (m_XAudio2 != NULL)
	{
		m_XAudio2->Release();
		m_XAudio2 = 0;
	}
	return true;
}

bool AudioEngine::AllPlayingStart()
{
	return true;
}

bool AudioEngine::AllPlayingStop()
{
	return true;
}

bool AudioEngine::AllPlayingPause()
{
	return true;
}

bool AudioEngine::AllPlayingRestart()
{
	return true;
}


IXAudio2* AudioEngine::GetXAudio2()
{
	return m_XAudio2;
}

float AudioEngine::GetEffectVolume()
{
	return extGameOption->GetEffectSoundVolume();
}

void AudioEngine::SetEffectVolume(float volume)
{
	extGameOption->SetEffectSoundValue(volume);
}

float AudioEngine::GetBackGroundVolume()
{
	return extGameOption->GetBackGroundSoundVolume();
}

void AudioEngine::SetBackGroundVolume(float volume)
{
	extGameOption->SetBackGroundSoundValue(volume);
}

