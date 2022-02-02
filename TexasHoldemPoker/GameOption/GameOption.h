#pragma once
#ifndef _GAMEOPTION_H_
#define _GAMEOPTION_H_
#include <cstdio>
#include <iostream>
#define MAX_VOLUME 2.0f
#define STANDARDWINDOW_WIDTH 1920
#define STANDARDWINDOW_HEIGHT 1080
// 기준 해상도는 1920 * 1080

class GameOption
{
private:
	int WindowWidth;
	int WindowHeight;

	float AllSoundValue;
	float EffectSoundValue;
	float BackGroundSoundValue;

	bool IsFullScreen;

	// 아직 미완성
private:
	bool ReadFile(FILE** fp);
	bool SaveFile(FILE** fp);

public:
	GameOption();
	GameOption(const GameOption& other);
	~GameOption();

	void Initialize();

	void SetWidth(int width);
	void SetHeight(int height);

	int GetWidth();
	int GetHeight();

	void SetAllSoundValue(float value);
	void SetEffectSoundValue(float value);
	void SetBackGroundSoundValue(float value);

	float GetAllSoundVolume();
	float GetEffectSoundVolume();
	float GetBackGroundSoundVolume();

	void SetFullScreen(bool Value);
	bool GetFullScreen();
};

#endif