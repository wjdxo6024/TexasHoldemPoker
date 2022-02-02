#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include "AudioEngine.h"
#include "../GameOption/GameOption.h"
#include "../Funtions/MyFunctions.h"

#ifdef _XBOX // 빅 엔디안
#define fourccRIFF 'RIFF'
#define fourccDATA 'data'
#define fourccFMT 'fmt '
#define fourccWAVE 'WAVE'
#define fourccXWMA 'XWMA'
#define fourccDPDS 'dpds'
#endif

#ifndef _XBOX // 리틀 엔디안
#define fourccRIFF 'FFIR'
#define fourccDATA 'atad'
#define fourccFMT ' tmf'
#define fourccWAVE 'EVAW'
#define fourccXWMA 'AMWX'
#define fourccDPDS 'sdpd'
#endif

enum SoundState { Sound_Idle, Sound_Stop, Sound_Play, Sound_Pause };

typedef struct  WAV_HEADER
{
	/* RIFF Chunk Descriptor */
	uint8_t         RIFF[4];        // RIFF Header Magic header
	uint32_t        ChunkSize;      // RIFF Chunk Size
	uint8_t         WAVE[4];        // WAVE Header
	/* "fmt" sub-chunk */
	uint8_t         fmt[4];         // FMT header
	uint32_t        Subchunk1Size;  // Size of the fmt chunk
	uint16_t        AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
	uint16_t        NumOfChannels;      // Number of channels 1=Mono 2=Sterio
	uint32_t        SamplesPerSec;  // Sampling Frequency in Hz
	uint32_t        bytesPerSec;    // bytes per second
	uint16_t        blockAlign;     // 2=16-bit mono, 4=16-bit stereo
	uint16_t        bitsPerSample;  // Number of bits per sample
	/* "data" sub-chunk */
	uint8_t         Subchunk2ID[4]; // "data"  string
	uint32_t        Subchunk2Size;  // Sampled data length
} wav_hdr;

// Wave File Data가 들어가는 곳

class Sound
{
protected:
	static int SoundCount;
	wav_hdr m_WaveHeader;
	WAVEFORMATEXTENSIBLE m_WFX;
	WAVEFORMATEX m_basicWFX;

	XAUDIO2_BUFFER m_Xaudio2buffer;
	BYTE* m_DataBuffer = nullptr;

	GameOption* extOption;
	AudioEngine* extEngine;
	IXAudio2SourceVoice* m_SourceVoice = nullptr;
protected:
	virtual HRESULT FindChunk(HANDLE hFile, DWORD fourcc, DWORD& dwcChunkSize, DWORD& dwChunkDataPosition);
	virtual HRESULT ReadChunkData(HANDLE hFile, void* buffer, DWORD buffersize, DWORD bufferoffset);
	virtual HRESULT ReadWave(const WCHAR* filePath);
public:
	Sound();
	Sound(const Sound& other);
	virtual ~Sound();

	virtual bool Initialize(const WCHAR* filepath, AudioEngine* engine);
	virtual bool InitializeBasic(const WCHAR* filepath, AudioEngine* engine, GameOption* option); // Header에 직접 웨이브 파일과 데이터를 읽는 방식
	virtual bool Update();
	virtual bool Play();
	virtual bool Pause();
	virtual bool Stop();
	virtual bool Restart();
	virtual bool Release();
};



