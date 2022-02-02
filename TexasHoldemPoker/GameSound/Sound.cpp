#include "Sound.h"

int Sound::SoundCount = 0;

HRESULT Sound::FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwChunkSize, DWORD& dwChunkDataPosition)
{
	HRESULT hr = S_OK;
	if (INVALID_SET_FILE_POINTER == SetFilePointer(hFile, 0, NULL, FILE_BEGIN))
		return HRESULT_FROM_WIN32(GetLastError());

	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD bytesRead = 0;
	DWORD dwOffset = 0;

	while (hr == S_OK)
	{
		DWORD dwRead;
		if (!ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());

		if (!ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
			hr = HRESULT_FROM_WIN32(GetLastError());

		switch (fourcc)
		{
		case fourccRIFF:
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (!ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
				hr = HRESULT_FROM_WIN32(GetLastError());
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT))
				return HRESULT_FROM_WIN32(GetLastError());
		}

		dwOffset += sizeof(DWORD) * 2;

		if (dwChunkType == fourcc)
		{
			dwChunkSize = dwChunkDataSize;
			dwChunkDataPosition = dwOffset;
			return S_OK;
		}

		dwOffset += dwChunkDataSize;

		if (bytesRead >= dwRIFFDataSize) return S_FALSE;
	}

	return S_OK;
}

HRESULT Sound::ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset)
{
	HRESULT hr = S_OK;
	if (SetFilePointer(hFile, bufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		return HRESULT_FROM_WIN32(GetLastError());
	
	DWORD dwRead;
	if (!ReadFile(hFile, buffer, buffersize, &dwRead, NULL))
		hr = HRESULT_FROM_WIN32(GetLastError());

	return hr;
}

HRESULT Sound::ReadWave(const WCHAR* filePath)
{
	return true;
}

Sound::Sound()
{
	SoundCount++;
}

Sound::Sound(const Sound& other)
{

}

Sound::~Sound()
{
	this->Release();
	if (SoundCount > 0)
		SoundCount--;
}

bool Sound::Initialize(const WCHAR* filepath, AudioEngine* engine)
{
	extEngine = engine;

	// Create And Set Buffer
	HRESULT hr;
	HANDLE hFile = CreateFile(filepath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Create Sound File Handle.", L"Error", MB_OK);
#endif
		return false;
	}


	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Set File Pointer.", L"Error", MB_OK);
#endif
		return false;
	}

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	if (FAILED(FindChunk(hFile, fourccRIFF, dwChunkSize, dwChunkPosition)))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Find Chunk.", L"Error", MB_OK);
#endif
		return false;
	}

	DWORD filetype;
	if (FAILED(ReadChunkData(hFile, &filetype, sizeof(DWORD), dwChunkPosition)))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Read Chunk Data.", L"Error", MB_OK);
#endif
		return false;
	}

	if (filetype != fourccWAVE)
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Is Not Wave.", L"Error", MB_OK);
#endif
		return false;
	}

	if (FAILED(FindChunk(hFile, fourccFMT, dwChunkSize, dwChunkPosition)))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Find FMT text.", L"Error", MB_OK);
#endif
			return false;
	}

	if (FAILED(ReadChunkData(hFile, &m_WFX, dwChunkSize, dwChunkPosition)))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Read WFX Data.", L"Error", MB_OK);
#endif
		return false;
	}
	
	if (FAILED(FindChunk(hFile, fourccDATA, dwChunkSize, dwChunkPosition)))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Find DATA text.", L"Error", MB_OK);
#endif
		return false;
	}
	
	m_DataBuffer = new BYTE[dwChunkSize];
	if (FAILED(ReadChunkData(hFile, m_DataBuffer, dwChunkSize, dwChunkPosition)))
	{
#ifdef _DEBUG
		MessageBox(NULL, L"Cannot Read Data.", L"Error", MB_OK);
#endif
		return false;
	}

	m_Xaudio2buffer.AudioBytes = dwChunkSize;
	m_Xaudio2buffer.pAudioData = m_DataBuffer;
	m_Xaudio2buffer.Flags = XAUDIO2_END_OF_STREAM;
	
	// Create Source Voice
	WAVEFORMATEX wfx = m_WFX.Format;
	hr = extEngine->GetXAudio2()->CreateSourceVoice(&m_SourceVoice, &wfx);
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

	return true;
}

bool Sound::InitializeBasic(const WCHAR* filepath, AudioEngine* engine, GameOption* option) // Header에 직접 웨이브 파일과 데이터를 읽는 방식
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

	return true;
}

bool Sound::Update()
{
	if (extEngine != NULL)
	{
		m_SourceVoice->SetVolume(extOption->GetAllSoundVolume());
	}
	return true;
}

bool Sound::Play()
{
	if (FAILED(m_SourceVoice->Start(0)))
		return false;
	return true;
}

bool Sound::Pause()
{
	if (FAILED(m_SourceVoice->Stop(0)))
		return false;
	return true;
}

bool Sound::Stop()
{
	return true;
}

bool Sound::Restart()
{
	return true;
}

bool Sound::Release()
{
	if (m_SourceVoice != NULL)
	{
		m_SourceVoice->DestroyVoice();
		m_SourceVoice = 0;
	}

	if (m_DataBuffer != NULL)
	{
		delete[] m_DataBuffer;
	}

	return true;
}