#pragma once
#include <queue>
#include <string>
#include "../AdvancedUI/TextOutputField.h"
#include "../../Funtions/MyFunctions.h"
// �˸� ���밡 ���� �ð����� �������� ���� (���� : ������ �˸� ����)
using namespace MyFunctions;

class NoticeAnimation
{
private:
	TextOutputField* m_OutputField; // �޼��� ��
	std::queue<std::wstring> m_MessageQueue; // �޼��� ť

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

