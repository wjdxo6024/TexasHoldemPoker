#pragma once
#include <ctime>
#include <chrono>

// ���� �и�������
// IsDescent�� Ʈ���� ��� ���� �ð��� 0���� ���� Ÿ�̸�
// false�� ��� ���� �ð��� Ư�� �ð��� ���� ���� Ÿ�̸�
class Timer
{
private:
	float m_OrigSec; // ������ ���� �ð�
	float m_TimerSec; // Ư���ð��� ��Ÿ���� Ÿ��.
	float m_CurrentSec; // ���� �ð�.
	bool m_IsDescent; // Ÿ�̸Ӱ� 0���� �� ������. Ȥ�� ���� �ð��� �� ������.
	bool m_IsActive;
	
	clock_t startClock;
	clock_t endClock;
public:
	Timer();

	bool StartTimer(float milliSec, bool m_IsDescent = true); // Ÿ�̸� ����
	bool StartTimer(int Sec, bool IsDescent = true); // Ÿ�̸� ����
	bool PauseTimer(); // Ÿ�̸� ���
	bool StopTimer();
	bool RestartTimer(); // Ÿ�̸� �����, �ݵ�� �̸� �������� �ʱ�ȭ �� ��.
	bool UpdateTimer(); // Ÿ�̸� ������Ʈ
	float ReturnTimer(); // ���� �ð� ���.
};

