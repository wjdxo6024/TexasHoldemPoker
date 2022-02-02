#include "Timer.h"

Timer::Timer()
{
	m_CurrentSec = 0;
	m_IsDescent = true;
	m_IsActive = false;
}

bool Timer::StartTimer(float miliSec, bool IsDescent) // Ÿ�̸� ����
{
	m_IsDescent = IsDescent;
	m_OrigSec = miliSec;
	if (m_IsDescent)
	{
		m_CurrentSec = miliSec;
		m_TimerSec = 0;
	}
	else
	{
		m_CurrentSec = 0;
		m_TimerSec = miliSec;
	}

	m_IsActive = true;
	startClock = clock();
	return true;
}

bool Timer::StartTimer(int Sec, bool IsDescent)
{
	m_IsDescent = IsDescent;
	m_OrigSec = Sec;
	if (m_IsDescent)
	{
		m_CurrentSec = Sec * 1000;
		m_TimerSec = 0;
	}
	else
	{
		m_CurrentSec = 0;
		m_TimerSec = Sec * 1000;
	}

	m_IsActive = true;
	startClock = clock();
	return true;
}

bool Timer::PauseTimer() // Ÿ�̸� ���
{
	if (m_IsActive)
		m_IsActive = false;
	else
	{
		startClock = clock();
		m_IsActive = true;
	}

	return true;
}

bool Timer::StopTimer()
{
	m_IsActive = false;

	if (m_IsDescent)
	{
		m_CurrentSec = m_OrigSec;
		m_TimerSec = 0;
	}
	else
	{
		m_CurrentSec = 0;
		m_TimerSec = m_OrigSec;
	}
	return true;
}

bool Timer::UpdateTimer() // Ÿ�̸� ������Ʈ
{
	if (m_IsActive)
	{
		endClock = clock();

		if (m_IsDescent)
		{
			m_CurrentSec -= (endClock - startClock);
			if (m_CurrentSec <= m_TimerSec)
			{
				m_IsActive = false;
				return false;
			}
		}
		else
		{
			m_CurrentSec += (endClock - startClock);
			if (m_CurrentSec >= m_TimerSec)
			{
				m_IsActive = false;
				return false;
			}
		}

		startClock = endClock;
	}

	return true;
}

float Timer::ReturnTimer() // ���� �ð� ���.
{
	return m_CurrentSec;
}