#pragma once
#ifndef _POKER_UI_H_
#define _POKER_UI_H_
#include "CustomTextOutputField.h";
#include "../BasicUI/CRectangle.h"
#include "../../PokerRule/PokerRule.h"
#include "../../Funtions/MyFunctions.h"
#include "CardImages.h"

using namespace MyFunctions;

class PokerUI
{
private:
	// Game UI, 0은 반드시 플레이어
	CustomTextOutputField* m_PhaseShow;
	CustomTextOutputField* m_EventShow;
	CRectangle* m_CardTable[5];

	// 0         4
	// 1         3
	//      2
	// 위의 UI 배치를 따른다.
	CustomTextOutputField* m_PlayersName[5];
	CustomTextOutputField* m_PlayersMoney[5];
	CustomTextOutputField* m_PlayersState[5];
	CRectangle* m_PlayersCard[10]; // 0~1, 2~3 ... 으로  나눔.

	Direct2DEngine* extEngine;
	GameOption* extGameOption;
	CardImages* extCardImages;
public:
	PokerUI();
	PokerUI(const PokerUI& other);
	virtual ~PokerUI();

	bool Initialize(Direct2DEngine* D2DEngine, GameOption* gameOption, CardImages* cardImages);
	bool Render();
	bool Update(Player* players);
	bool Update();
	bool Release();

	bool SetPlayersData(Player* players, int index); // UI에 플레이어의 정보를 채운다.
	bool ShowPlayersTurn(int index); // 대상 플레이어가 턴상태이면 다르게 출력. 

	bool CardSet();

};

#endif
