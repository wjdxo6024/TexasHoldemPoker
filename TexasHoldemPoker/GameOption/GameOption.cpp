#include "GameOption.h"

GameOption::GameOption()
{
	WindowHeight = 768;
	WindowWidth = 1024;

	this->SetAllSoundValue(1.0);
	this->SetEffectSoundValue(1.0);
	this->SetBackGroundSoundValue(1.0);

	IsFullScreen = false;
}

GameOption::GameOption(const GameOption& other)
{

}

GameOption::~GameOption()
{

}

void GameOption::Initialize()
{
	// 파일을 불러와 초기화를 실시한다.
}

void GameOption::SetWidth(int width)
{
	WindowWidth = width;
}

void GameOption::SetHeight(int height)
{
	WindowHeight = height;
}

int GameOption::GetWidth()
{
	return WindowWidth;
}

int GameOption::GetHeight()
{
	return WindowHeight;
}

void GameOption::SetAllSoundValue(float value)
{
	if (value > MAX_VOLUME)
		AllSoundValue = MAX_VOLUME;
	else if (value < 0)
		AllSoundValue = 0;
	else
		AllSoundValue = value;
}

void GameOption::SetEffectSoundValue(float value)
{
	if (value > MAX_VOLUME)
		EffectSoundValue = MAX_VOLUME;
	else if (value < 0)
		EffectSoundValue = 0;
	else
		EffectSoundValue = value;
}

void GameOption::SetBackGroundSoundValue(float value)
{
	if (value > MAX_VOLUME)
		BackGroundSoundValue = MAX_VOLUME;
	else if (value < 0)
		BackGroundSoundValue = 0;
	else
		BackGroundSoundValue = value;
}

float GameOption::GetAllSoundVolume()
{
	return AllSoundValue;
}

float GameOption::GetEffectSoundVolume()
{
	return EffectSoundValue;
}

float GameOption::GetBackGroundSoundVolume()
{
	return BackGroundSoundValue;
}

void GameOption::SetFullScreen(bool Value)
{
	IsFullScreen = Value;
}

bool GameOption::GetFullScreen()
{
	return IsFullScreen;
}
