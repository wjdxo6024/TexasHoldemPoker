#pragma once
#include <ctime>
#include <chrono>
#include <Windows.h>
// Delta Time�� ���� Ŭ����.

class GameTime
{
private:
	double m_dDeltaTime;
	float m_fDeltaTime; // ���� �����Ӵ� Ÿ��
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

