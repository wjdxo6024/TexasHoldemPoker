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
	// Game UI, 0�� �ݵ�� �÷��̾�
	CustomTextOutputField* m_PhaseShow;
	CustomTextOutputField* m_EventShow;
	CRectangle* m_CardTable[5];

	// 0         4
	// 1         3
	//      2
	// ���� UI ��ġ�� ������.
	CustomTextOutputField* m_PlayersName[5];
	CustomTextOutputField* m_PlayersMoney[5];
	CustomTextOutputField* m_PlayersState[5];
	CRectangle* m_PlayersCard[10]; // 0~1, 2~3 ... ����  ����.

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

	bool SetPlayersData(Player* players, int index); // UI�� �÷��̾��� ������ ä���.
	bool ShowPlayersTurn(int index); // ��� �÷��̾ �ϻ����̸� �ٸ��� ���. 

	bool CardSet();

};

#endif
