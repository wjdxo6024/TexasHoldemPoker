#pragma once
#include "PokerRule.h"
// 내부 시스템으로서 블라인드, 턴 등 내부 요소 결정 및 출력

class PokerSystem
{
private:
	int m_PlayerCount;

public:
	bool Initialize();
};

