#include "PokerUI.h"

PokerUI::PokerUI()
{

}

PokerUI::PokerUI(const PokerUI& other)
{

}

PokerUI::~PokerUI()
{

}

bool PokerUI::Initialize(Direct2DEngine* D2DEngine, GameOption* gameOption, CardImages* cardImages)
{
	extEngine = D2DEngine;
	extGameOption = gameOption;
	extCardImages = cardImages;

	// 테이블 UI

	int CardTableX = (extGameOption->GetWidth() / 2) + ScalingUI_X(extCardImages->GetCardWidth() / 2, extGameOption->GetWidth())
		+ ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()) +
		ScalingUI_X(20 * 2, extGameOption->GetWidth());
	for (int i = 0; i < 5; i++)
	{
		m_CardTable[i] = new CRectangle;
		m_CardTable[i]->Initialize(extEngine, CardTableX,
			(extGameOption->GetHeight() / 2) - ScalingUI_Y(extCardImages->GetCardHeight() / 2, extGameOption->GetHeight()),
			ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()));
		m_CardTable[i]->SetColor(D2D1::ColorF::White);
		m_CardTable[i]->SetStroke(2.0f);
		m_CardTable[i]->SetRound(true);
		CardTableX += -(ScalingUI_X(20, extGameOption->GetWidth()) + ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()));
	}

	// 플레이어 UI
	// Player 0 ------------------------------------------
	m_PlayersName[0] = new CustomTextOutputField;
	if (m_PlayersName[0] != NULL)
	{

	}
	else
		return false;

	m_PlayersMoney[0] = new CustomTextOutputField;
	m_PlayersState[0] = new CustomTextOutputField;

	m_PlayersCard[0];
	m_PlayersCard[1];

	// ---------------------------------------------------

	// Player 1 ------------------------------------------

	// ---------------------------------------------------

	// Player 2 ------------------------------------------

	// ---------------------------------------------------

	// Player 3 ------------------------------------------

	// ---------------------------------------------------

	// Player 4 ------------------------------------------

	// ---------------------------------------------------

	return true;
}

bool PokerUI::Render()
{
	for (int i = 0; i < 5; i++)
	{
		m_CardTable[i]->Draw();
	}
	return true;
}

bool PokerUI::Update(Player* players)
{
	return true;
}

bool PokerUI::Update()
{
	return true;
}

bool PokerUI::Release()
{
	for (int i = 0; i < 5; i++)
	{
		SAFE_RELEASE_AND_DELETE(m_CardTable[i]);
	}
	return true;
}

bool PokerUI::SetPlayersData(Player* players, int index) // UI에 플레이어의 정보를 채운다.
{
	return true;
}

bool PokerUI::ShowPlayersTurn(int index) // 대상 플레이어가 턴상태이면 다르게 출력. 
{
	return true;
}

bool PokerUI::CardSet()
{
	return true;
}