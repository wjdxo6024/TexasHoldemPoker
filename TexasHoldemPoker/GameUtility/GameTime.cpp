#include "GameTime.h"

GameTime::GameTime()
{

}

GameTime::GameTime(const GameTime& other)
{

}

GameTime::~GameTime()
{

}

bool GameTime::Initialize()
{
	QueryPerformanceFrequency(&m_PeriodFrequency);

	QueryPerformanceCounter(&m_LastTime);

	m_TimeScale = 1.0;
	return true;
}

bool GameTime::Update()
{
	QueryPerformanceCounter(&m_CurrentTime);

	m_dDeltaTime = (double)(m_CurrentTime.QuadPart - m_LastTime.QuadPart) / m_PeriodFrequency.QuadPart * m_TimeScale;

	m_fDeltaTime = static_cast<float>(m_dDeltaTime);
	m_LastTime = m_CurrentTime;
	
	return true;
}

float GameTime::GetDeltaTime()
{
	return m_fDeltaTime;
}

double GameTime::GetDoubleDeltaTime()
{
	return m_dDeltaTime;
}