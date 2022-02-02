#pragma once
#include <ctime>
#include <chrono>
#include <Windows.h>
// Delta Time을 위한 클래스.

class GameTime
{
private:
	double m_dDeltaTime;
	float m_fDeltaTime; // 현재 프레임당 타임
	LARGE_INTEGER m_PeriodFrequency;
	LARGE_INTEGER m_LastTime;
	LARGE_INTEGER m_CurrentTime;
	double m_TimeScale;
public:
	GameTime();
	GameTime(const GameTime& other);
	virtual ~GameTime();

	bool Initialize();
	bool Update();

	float GetDeltaTime();
	double GetDoubleDeltaTime();
};

