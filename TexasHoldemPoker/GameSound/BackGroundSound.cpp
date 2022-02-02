#include "BackGroundSound.h"

BackGroundSound::BackGroundSound()
{

}

BackGroundSound::BackGroundSound(const BackGroundSound& other)
{

}

BackGroundSound::~BackGroundSound()
{
	this->Release();
}

bool BackGroundSound::InitializeBasic(const WCHAR* filepath, AudioEngine* engine, GameOption* option)
{
	extEngine = engine;
	extOption = option;

	FILE* fp = NULL;
	if (_waccess(filepath, 0))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Find Wav File.", L"Error", MB_OK);
#endif
		return false;
	}

	fp = _wfopen(filepath, L"rb");
	if (fp == NULL)
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Open Wav File.", L"Error", MB_OK);
#endif
		return false;
	}

	size_t bytesRead = fread(&m_WaveHeader, sizeof(wav_hdr), 1, fp);
	if (bytesRead < 0)
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Failed To Read Wav Header.", L"Error", MB_OK);
#endif
		return false;
	}
	m_basicWFX.wFormatTag = WAVE_FORMAT_PCM;
	m_basicWFX.nChannels = m_WaveHeader.NumOfChannels;
	m_basicWFX.nBlockAlign = m_WaveHeader.blockAlign;
	m_basicWFX.wBitsPerSample = m_WaveHeader.bitsPerSample;
	m_basicWFX.nSamplesPerSec = m_WaveHeader.SamplesPerSec;
	m_basicWFX.nAvgBytesPerSec = m_WaveHeader.SamplesPerSec * m_WaveHeader.blockAlign;
	m_basicWFX.cbSize = 0;

	// Data Read ---------------------------------------------------------
	const int BUFFER_SIZE = 4096;
	int LeftChunkSize = MyFunctions::GetFileSize(fp) - ftell(fp);
	int TmpChunkSize = LeftChunkSize;
	BYTE TmpBuffer[BUFFER_SIZE];
	m_DataBuffer = new BYTE[TmpChunkSize];
	int i = 0;
	while (TmpChunkSize > 0)
	{
		if (TmpChunkSize < 4096)
			bytesRead = fread(&TmpBuffer, sizeof BYTE, TmpChunkSize, fp);
		else
			bytesRead = fread(&TmpBuffer, sizeof BYTE, BUFFER_SIZE, fp);
		TmpChunkSize -= bytesRead;
		if (bytesRead == 0)
			break;

		memcpy(m_DataBuffer + i, TmpBuffer, bytesRead);
		i += bytesRead;
	}
	// --------------------------------------------------------------------

	fclose(fp);

	m_Xaudio2buffer.AudioBytes = LeftChunkSize;
	m_Xaudio2buffer.pAudioData = m_DataBuffer;
	m_Xaudio2buffer.Flags = XAUDIO2_END_OF_STREAM;
	// Loop
	m_Xaudio2buffer.LoopBegin = 0;
	m_Xaudio2buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	m_Xaudio2buffer.LoopLength = 0; // 전체 버퍼
	m_Xaudio2buffer.PlayBegin = 0;
	m_Xaudio2buffer.PlayLength = 0; // 전체 버퍼
	m_Xaudio2buffer.pContext = NULL;

	HRESULT hr = engine->GetXAudio2()->CreateSourceVoice(&m_SourceVoice, &m_basicWFX);
	if (FAILED(hr))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create Source Voice.", L"Error", MB_OK);
#endif
		return false;
	}

	if (FAILED(m_SourceVoice->SubmitSourceBuffer(&m_Xaudio2buffer)))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Sumbit Source Buffer.", L"Error", MB_OK);
#endif
		return false;
	}

	m_State = Sound_Idle;

	Update();
	return true;
}

bool BackGroundSound::Update()
{
	Sound::m_SourceVoice->SetVolume(extOption->GetBackGroundSoundVolume());
	return true;
}

bool BackGroundSound::Play()
{
	if (m_State == Sound_Play)
		return false;

	if (m_State == Sound_Stop)
	{
		Sound::m_SourceVoice->FlushSourceBuffers();
		Sound::m_SourceVoice->SubmitSourceBuffer(&m_Xaudio2buffer);
	}
	Sound::m_SourceVoice->SetVolume(extOption->GetBackGroundSoundVolume());
	Sound::Play();
	m_State == Sound_Play;
	return true;
}

bool BackGroundSound::Pause()
{
	if (Sound::Pause())
		m_State = Sound_Pause;
	else
		return false;
	return true;
}

bool BackGroundSound::Stop()
{
	if (Sound::Pause())
		m_State = Sound_Stop;
	else
		return false;

	return true;
}

bool BackGroundSound::Restart()
{
	this->Stop();
	this->Play();
	return true;
}

bool BackGroundSound::Release()
{
	return true;
}