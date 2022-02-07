#pragma once
#include <queue>
#include <string>
#include "../AdvancedUI/TextOutputField.h"
#include "../../Funtions/MyFunctions.h"
// 알림 막대가 일정 시간동안 보여지는 형태 (예시 : 웜즈의 알림 막대)
using namespace MyFunctions;

class NoticeAnimation
{
private:
	TextOutputField* m_OutputField; // 메세지 바
	std::queue<std::wstring> m_MessageQueue; // 메세지 큐

	bool Is_Animate;

	Direct2DEngine* extEngine;
	GameOption* extGameOption;

	float m_AnimationValue;
	float m_TempValue;
public:
	bool Initialize(Direct2DEngine* D2DEngine, GameOption* gameOption);
	bool Render();
	bool Update(float deltaTime);
	bool Release();

	bool InputMessage(const WCHAR* Message);
};

