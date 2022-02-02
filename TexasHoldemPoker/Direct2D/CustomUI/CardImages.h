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
	bool Draw(int x, int y, Card& card); // 카드를 받고 이를 출력.
	bool Update();
	bool Update(double deltaTime); // 애니메이션 용 업데이트
	bool Release();

	float GetCardWidth();
	float GetCardHeight();

	bool CardRotate(); // 카드 회전
};

