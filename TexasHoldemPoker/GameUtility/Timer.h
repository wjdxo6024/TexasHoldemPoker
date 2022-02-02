#pragma once
#include <ctime>
#include <chrono>

// 기준 밀리세컨드
// IsDescent가 트루일 경우 현재 시간이 0으로 가는 타이머
// false일 경우 현재 시간이 특정 시간을 향해 가는 타이머
class Timer
{
private:
	float m_OrigSec; // 지정한 원래 시간
	float m_TimerSec; // 특정시간을 나타내는 타임.
	float m_CurrentSec; // 현재 시간.
	bool m_IsDescent; // 타이머가 0으로 갈 것인지. 혹은 정한 시간에 갈 것인지.
	bool m_IsActive;
	
	clock_t startClock;
	clock_t endClock;
public:
	Timer();

	bool StartTimer(float milliSec, bool m_IsDescent = true); // 타이머 시작
	bool StartTimer(int Sec, bool IsDescent = true); // 타이머 시작
	bool PauseTimer(); // 타이머 대기
	bool StopTimer();
	bool RestartTimer(); // 타이머 재시작, 반드시 미리 시작으로 초기화 할 것.
	bool UpdateTimer(); // 타이머 업데이트
	float ReturnTimer(); // 현재 시간 출력.
};

