#pragma once
#include "../BasicUI/CBitmap.h"
#include "../../Funtions/MyFunctions.h"
#include "../../PokerRule/PokerDefine.h"

using namespace MyFunctions;

class CardImages :
	public CBitmap
{
private:
	float m_CardWidth;
	float m_CardHeight;

	GameOption* extGameOption;
public:
	bool Initialize(Direct2DEngine* pD2DEngine, GameOption* gameOption, WCHAR* filePath);
	bool Draw(int x, int y);
	bool Draw(int x, int y, Card& card); // ī�带 �ް� �̸� ���.
	bool Update();
	bool Update(double deltaTime); // �ִϸ��̼� �� ������Ʈ
	bool Release();

	float GetCardWidth();
	float GetCardHeight();

	bool CardRotate(); // ī�� ȸ��
};

