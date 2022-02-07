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

	int CardTableX = (extGameOption->GetWidth() / 2) + ScalingUI_X(extCardImages->GetCardWidth() / 2, extGameOption->GetWidth()) +
		ScalingUI_X(20, extGameOption->GetWidth());
	for (int i = 0; i < 3; i++)
	{
		m_CardTable[i] = new CRectangle;
		m_CardTable[i]->Initialize(extEngine, CardTableX,
			(extGameOption->GetHeight() / 2) - ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()) - ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()));
		m_CardTable[i]->SetColor(D2D1::ColorF::White);
		m_CardTable[i]->SetStroke(2.0f);
		m_CardTable[i]->SetRound(true);
		CardTableX += -(ScalingUI_X(20, extGameOption->GetWidth()) + ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()));
	}

	CardTableX = (extGameOption->GetWidth() / 2) + ScalingUI_X(20, extGameOption->GetWidth());
	for (int i = 3; i < 5; i++)
	{
		m_CardTable[i] = new CRectangle;
		m_CardTable[i]->Initialize(extEngine, CardTableX,
			(extGameOption->GetHeight() / 2) - ScalingUI_Y(80, extGameOption->GetHeight()),
			ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()));
		m_CardTable[i]->SetColor(D2D1::ColorF::White);
		m_CardTable[i]->SetStroke(2.0f);
		m_CardTable[i]->SetRound(true);
		CardTableX += -(ScalingUI_X(20, extGameOption->GetWidth()) + ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()));
	}

	// 플레이어 UI
	// Player 0 ------------------------------------------
	m_PlayersName[0] = new TextOutputField;
	if (m_PlayersName[0] != NULL)
	{
		m_PlayersName[0]->Initialize(extEngine, 5, ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersName[0]->CreateRectangle();
		m_PlayersName[0]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersName[0]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersName[0]->GetText()->SetFontSize(m_PlayersName[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersMoney[0] = new TextOutputField;
	if (m_PlayersMoney[0] != NULL)
	{
		m_PlayersMoney[0]->Initialize(extEngine, 5, ScalingUI_Y(100 + (extCardImages->GetCardHeight() / 3), extGameOption->GetHeight()),
			ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersMoney[0]->CreateRectangle();
		m_PlayersMoney[0]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersMoney[0]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersMoney[0]->GetText()->SetFontSize(m_PlayersMoney[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersState[0] = new TextOutputField;
	if (m_PlayersState[0] != NULL)
	{
		m_PlayersState[0]->Initialize(extEngine, 5, ScalingUI_Y(100 + (extCardImages->GetCardHeight() / 3 * 2), extGameOption->GetHeight()),
			ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersState[0]->CreateRectangle();
		m_PlayersState[0]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersState[0]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersState[0]->GetText()->SetFontSize(m_PlayersState[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersCard[0] = new CRectangle;
	if (m_PlayersCard[0] != NULL)
	{
		m_PlayersCard[0]->Initialize(extEngine, 5 + ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()));
		m_PlayersCard[0]->SetColor(D2D1::ColorF::White);
	}
	else
		return false;

	m_PlayersCard[1] = new CRectangle;
	if (m_PlayersCard[1] != NULL)
	{
		m_PlayersCard[1]->Initialize(extEngine, 5 + ScalingUI_X(200, extGameOption->GetWidth()) + ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()));
		m_PlayersCard[1]->SetColor(D2D1::ColorF::White);
	}
	else
		return false;

	// ---------------------------------------------------

	// Player 1 ------------------------------------------

	m_PlayersName[1] = new TextOutputField;
	if (m_PlayersName[1] != NULL)
	{
		m_PlayersName[1]->Initialize(extEngine, 5, ScalingUI_Y(450, extGameOption->GetHeight()),
			ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersName[1]->CreateRectangle();
		m_PlayersName[1]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersName[1]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersName[1]->GetText()->SetFontSize(m_PlayersName[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersMoney[1] = new TextOutputField;
	if (m_PlayersMoney[1] != NULL)
	{
		m_PlayersMoney[1]->Initialize(extEngine, 5, ScalingUI_Y(450 + (extCardImages->GetCardHeight() / 3), extGameOption->GetHeight()),
			ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersMoney[1]->CreateRectangle();
		m_PlayersMoney[1]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersMoney[1]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersMoney[1]->GetText()->SetFontSize(m_PlayersMoney[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersState[1] = new TextOutputField;
	if (m_PlayersState[1] != NULL)
	{
		m_PlayersState[1]->Initialize(extEngine, 5, ScalingUI_Y(450 + (extCardImages->GetCardHeight() / 3 * 2), extGameOption->GetHeight()),
			ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersState[1]->CreateRectangle();
		m_PlayersState[1]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersState[1]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersState[1]->GetText()->SetFontSize(m_PlayersState[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersCard[2] = new CRectangle;
	if (m_PlayersCard[2] != NULL)
	{
		m_PlayersCard[2]->Initialize(extEngine, 5 + ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(450, extGameOption->GetHeight()),
			ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()));
		m_PlayersCard[2]->SetColor(D2D1::ColorF::White);
	}
	else
		return false;

	m_PlayersCard[3] = new CRectangle;
	if (m_PlayersCard[3] != NULL)
	{
		m_PlayersCard[3]->Initialize(extEngine, 5 + ScalingUI_X(200, extGameOption->GetWidth()) + ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(450, extGameOption->GetHeight()),
			ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()));
		m_PlayersCard[3]->SetColor(D2D1::ColorF::White);
	}
	else
		return false;
	
	// ---------------------------------------------------

	// Player 2(플레이어 자신) ---------------------------
	m_PlayersName[2] = new TextOutputField;
	if (m_PlayersName[2] != NULL)
	{
		m_PlayersName[2]->Initialize(extEngine, extGameOption->GetWidth() / 2 + ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()) + ScalingUI_X(50, extGameOption->GetWidth()),
			ScalingUI_Y(800, extGameOption->GetHeight()),
			ScalingUI_X(400, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersName[2]->CreateRectangle();
		m_PlayersName[2]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersName[2]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersName[2]->GetText()->SetFontSize(m_PlayersName[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersMoney[2] = new TextOutputField;
	if (m_PlayersMoney[2] != NULL)
	{
		m_PlayersMoney[2]->Initialize(extEngine, extGameOption->GetWidth() / 2 + ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()) + ScalingUI_X(50, extGameOption->GetWidth()),
			ScalingUI_Y(800 + (extCardImages->GetCardHeight() / 3), extGameOption->GetHeight()),
			ScalingUI_X(400, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersMoney[2]->CreateRectangle();
		m_PlayersMoney[2]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersMoney[2]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersMoney[2]->GetText()->SetFontSize(m_PlayersMoney[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersState[2] = new TextOutputField;
	if (m_PlayersState[2] != NULL)
	{
		m_PlayersState[2]->Initialize(extEngine, extGameOption->GetWidth() / 2 + ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()) + ScalingUI_X(50, extGameOption->GetWidth()),
			ScalingUI_Y(800 + (extCardImages->GetCardHeight() / 3 * 2), extGameOption->GetHeight()),
			ScalingUI_X(400, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersState[2]->CreateRectangle();
		m_PlayersState[2]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersState[2]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersState[2]->GetText()->SetFontSize(m_PlayersState[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersCard[4] = new CRectangle;
	if (m_PlayersCard[4] != NULL)
	{
		m_PlayersCard[4]->Initialize(extEngine, extGameOption->GetWidth() / 2,
			ScalingUI_Y(800, extGameOption->GetHeight()),
			ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()));
		m_PlayersCard[4]->SetColor(D2D1::ColorF::White);
	}
	else
		return false;

	m_PlayersCard[5] = new CRectangle;
	if (m_PlayersCard[5] != NULL)
	{
		m_PlayersCard[5]->Initialize(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(800, extGameOption->GetHeight()),
			ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()));
		m_PlayersCard[5]->SetColor(D2D1::ColorF::White);
	}
	else
		return false;

	m_FoldButton = new MainMenuButton;
	if (m_FoldButton != NULL)
	{
		m_FoldButton->InitializeEx(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()) - ScalingUI_X(450, extGameOption->GetWidth()),
			ScalingUI_Y(800, extGameOption->GetHeight()),
			ScalingUI_X(400, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()), const_cast<WCHAR*>(L"Fold"));

		reinterpret_cast<CRectangle*>(m_FoldButton->GetShape())->SetRound(true);
		m_FoldButton->SetEvent(ButtonEvent::ButtonEvent_SinglePlay_Fold);
	}
	else
		return false;

	m_CallButton = new MainMenuButton;
	if (m_CallButton != NULL)
	{
		m_CallButton->InitializeEx(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()) - ScalingUI_X(450, extGameOption->GetWidth()),
			ScalingUI_Y(800 + (extCardImages->GetCardHeight() / 3), extGameOption->GetHeight()),
			ScalingUI_X(400, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()), const_cast<WCHAR*>(L"Call"));

		reinterpret_cast<CRectangle*>(m_CallButton->GetShape())->SetRound(true);
		m_CallButton->SetEvent(ButtonEvent::ButtonEvent_SinglePlay_Call);
	}
	else
		return false;

	m_RaiseButton = new MainMenuButton;
	if (m_RaiseButton != NULL)
	{
		m_RaiseButton->InitializeEx(extEngine, extGameOption->GetWidth() / 2 - ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()) - ScalingUI_X(450, extGameOption->GetWidth()),
			ScalingUI_Y(800 + (extCardImages->GetCardHeight() / 3 * 2), extGameOption->GetHeight()),
			ScalingUI_X(400, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()), const_cast<WCHAR*>(L"Raise"));

		reinterpret_cast<CRectangle*>(m_RaiseButton->GetShape())->SetRound(true);
		m_RaiseButton->SetEvent(ButtonEvent::ButtonEvent_SinglePlay_Raise);
	}
	else
		return false;
	// ---------------------------------------------------

	// Player 3 ------------------------------------------

	m_PlayersName[3] = new TextOutputField;
	if (m_PlayersName[3] != NULL)
	{
		m_PlayersName[3]->Initialize(extEngine, extGameOption->GetWidth() - 5 - ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(450, extGameOption->GetHeight()),
			ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersName[3]->CreateRectangle();
		m_PlayersName[3]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersName[3]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersName[3]->GetText()->SetFontSize(m_PlayersName[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersMoney[3] = new TextOutputField;
	if (m_PlayersMoney[3] != NULL)
	{
		m_PlayersMoney[3]->Initialize(extEngine, extGameOption->GetWidth() - 5 - ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(450 + (extCardImages->GetCardHeight() / 3), extGameOption->GetHeight()),
			ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersMoney[3]->CreateRectangle();
		m_PlayersMoney[3]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersMoney[3]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersMoney[3]->GetText()->SetFontSize(m_PlayersMoney[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersState[3] = new TextOutputField;
	if (m_PlayersState[3] != NULL)
	{
		m_PlayersState[3]->Initialize(extEngine, extGameOption->GetWidth() - 5 - ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(450 + (extCardImages->GetCardHeight() / 3 * 2), extGameOption->GetHeight()),
			ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersState[3]->CreateRectangle();
		m_PlayersState[3]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersState[3]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersState[3]->GetText()->SetFontSize(m_PlayersState[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersCard[6] = new CRectangle;
	if (m_PlayersCard[6] != NULL)
	{
		m_PlayersCard[6]->Initialize(extEngine, extGameOption->GetWidth() - 5 - ScalingUI_X(200, extGameOption->GetWidth()) - ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(450, extGameOption->GetHeight()),
			ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()));
		m_PlayersCard[6]->SetColor(D2D1::ColorF::White);
	}
	else
		return false;

	m_PlayersCard[7] = new CRectangle;
	if (m_PlayersCard[7] != NULL)
	{
		m_PlayersCard[7]->Initialize(extEngine, extGameOption->GetWidth() - 5 - ScalingUI_X(200, extGameOption->GetWidth()) - ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()) * 2,
			ScalingUI_Y(450, extGameOption->GetHeight()),
			ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()));
		m_PlayersCard[7]->SetColor(D2D1::ColorF::White);
	}
	else
		return false;

	// ---------------------------------------------------

	// Player 4 ------------------------------------------

	m_PlayersName[4] = new TextOutputField;
	if (m_PlayersName[4] != NULL)
	{
		m_PlayersName[4]->Initialize(extEngine, extGameOption->GetWidth() - 5 - ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersName[4]->CreateRectangle();
		m_PlayersName[4]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersName[4]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersName[4]->GetText()->SetFontSize(m_PlayersName[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersMoney[4] = new TextOutputField;
	if (m_PlayersMoney[4] != NULL)
	{
		m_PlayersMoney[4]->Initialize(extEngine, extGameOption->GetWidth() - 5 - ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(100 + (extCardImages->GetCardHeight() / 3), extGameOption->GetHeight()),
			ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersMoney[4]->CreateRectangle();
		m_PlayersMoney[4]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersMoney[4]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersMoney[4]->GetText()->SetFontSize(m_PlayersMoney[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersState[4] = new TextOutputField;
	if (m_PlayersState[4] != NULL)
	{
		m_PlayersState[4]->Initialize(extEngine, extGameOption->GetWidth() - 5 - ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(100 + (extCardImages->GetCardHeight() / 3 * 2), extGameOption->GetHeight()),
			ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight() / 3, extGameOption->GetHeight()));
		m_PlayersState[4]->CreateRectangle();
		m_PlayersState[4]->SetTextContent(const_cast<WCHAR*>(L""));
		m_PlayersState[4]->GetRect()->SetColor(D2D1::ColorF::White);
		m_PlayersState[4]->GetText()->SetFontSize(m_PlayersState[0]->GetText()->GetFontSize() * 1.3f);
	}
	else
		return false;

	m_PlayersCard[8] = new CRectangle;
	if (m_PlayersCard[8] != NULL)
	{
		m_PlayersCard[8]->Initialize(extEngine, extGameOption->GetWidth() - 5 - ScalingUI_X(200, extGameOption->GetWidth()) - ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()));
		m_PlayersCard[8]->SetColor(D2D1::ColorF::White);
	}
	else
		return false;

	m_PlayersCard[9] = new CRectangle;
	if (m_PlayersCard[9] != NULL)
	{
		m_PlayersCard[9]->Initialize(extEngine, extGameOption->GetWidth() - 5 - ScalingUI_X(200, extGameOption->GetWidth()) - ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()) * 2,
			ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_X(extCardImages->GetCardWidth(), extGameOption->GetWidth()),
			ScalingUI_Y(extCardImages->GetCardHeight(), extGameOption->GetHeight()));
		m_PlayersCard[9]->SetColor(D2D1::ColorF::White);
	}
	else
		return false;

	// ---------------------------------------------------

	return true;
}

bool PokerUI::Render()
{
	for (int i = 0; i < 5; i++)
	{
		m_CardTable[i]->Draw();
	}

	m_PlayersName[0]->Render();
	m_PlayersMoney[0]->Render();
	m_PlayersState[0]->Render();
	m_PlayersCard[0]->Draw();
	m_PlayersCard[1]->Draw();

	m_PlayersName[1]->Render();
	m_PlayersMoney[1]->Render();
	m_PlayersState[1]->Render();
	m_PlayersCard[2]->Draw();
	m_PlayersCard[3]->Draw();

	m_PlayersName[2]->Render();
	m_PlayersMoney[2]->Render();
	m_PlayersState[2]->Render();
	m_PlayersCard[4]->Draw();
	m_PlayersCard[5]->Draw();

	m_FoldButton->Render();
	m_CallButton->Render();
	m_RaiseButton->Render();

	m_PlayersName[3]->Render();
	m_PlayersMoney[3]->Render();
	m_PlayersState[3]->Render();
	m_PlayersCard[6]->Draw();
	m_PlayersCard[7]->Draw();

	m_PlayersName[4]->Render();
	m_PlayersMoney[4]->Render();
	m_PlayersState[4]->Render();
	m_PlayersCard[8]->Draw();
	m_PlayersCard[9]->Draw();
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
	// Player 4
	SAFE_RELEASE_AND_DELETE(m_PlayersCard[9]);
	SAFE_RELEASE_AND_DELETE(m_PlayersCard[8]);
	SAFE_RELEASE_AND_DELETE(m_PlayersState[4]);
	SAFE_RELEASE_AND_DELETE(m_PlayersMoney[4]);
	SAFE_RELEASE_AND_DELETE(m_PlayersName[4]);

	// Player 3
	SAFE_RELEASE_AND_DELETE(m_PlayersCard[7]);
	SAFE_RELEASE_AND_DELETE(m_PlayersCard[6]);
	SAFE_RELEASE_AND_DELETE(m_PlayersState[3]);
	SAFE_RELEASE_AND_DELETE(m_PlayersMoney[3]);
	SAFE_RELEASE_AND_DELETE(m_PlayersName[3]);

	// Player 2
	SAFE_RELEASE_AND_DELETE(m_RaiseButton);
	SAFE_RELEASE_AND_DELETE(m_CallButton);
	SAFE_RELEASE_AND_DELETE(m_FoldButton);

	SAFE_RELEASE_AND_DELETE(m_PlayersCard[5]);
	SAFE_RELEASE_AND_DELETE(m_PlayersCard[4]);
	SAFE_RELEASE_AND_DELETE(m_PlayersState[2]);
	SAFE_RELEASE_AND_DELETE(m_PlayersMoney[2]);
	SAFE_RELEASE_AND_DELETE(m_PlayersName[2]);

	// Player 1
	SAFE_RELEASE_AND_DELETE(m_PlayersCard[3]);
	SAFE_RELEASE_AND_DELETE(m_PlayersCard[2]);
	SAFE_RELEASE_AND_DELETE(m_PlayersState[1]);
	SAFE_RELEASE_AND_DELETE(m_PlayersMoney[1]);
	SAFE_RELEASE_AND_DELETE(m_PlayersName[1]);


	// Player 0
	SAFE_RELEASE_AND_DELETE(m_PlayersCard[1]);
	SAFE_RELEASE_AND_DELETE(m_PlayersCard[0]);
	SAFE_RELEASE_AND_DELETE(m_PlayersState[0]);
	SAFE_RELEASE_AND_DELETE(m_PlayersMoney[0]);
	SAFE_RELEASE_AND_DELETE(m_PlayersName[0]);

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

bool PokerUI::DisabledActionButton()
{
	m_FoldButton->Disabled();
	m_CallButton->Disabled();
	m_RaiseButton->Disabled();

	return true;
}

bool PokerUI::CardSet()
{
	return true;
}

ButtonEvent PokerUI::PokerUIFunc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, int x, int y, bool IsAnimate)
{
	if (!IsAnimate) // 버튼 비활성화
	{
		switch (message)
		{
		case WM_MOUSEMOVE:
			if (m_FoldButton->IsInside(x, y))
			{
				m_FoldButton->Touched();
				break;
			}
			else
				m_FoldButton->Normally();

			if (m_CallButton->IsInside(x, y))
			{
				m_CallButton->Touched();
				break;
			}
			else
				m_CallButton->Normally();

			if (m_RaiseButton->IsInside(x, y))
			{
				m_RaiseButton->Touched();
				break;
			}
			else
				m_RaiseButton->Normally();

			break;
		case WM_LBUTTONDOWN: // Mouse Click & Event
			if (m_FoldButton->IsInside(x, y))
			{
				m_FoldButton->Pressed();
				break;
			}

			if (m_CallButton->IsInside(x, y))
			{
				m_CallButton->Pressed();
				break;
			}

			if (m_RaiseButton->IsInside(x, y))
			{
				m_RaiseButton->Pressed();
				break;
			}

			break;
		case WM_LBUTTONUP: // 버튼 이벤트 처리
			if (m_FoldButton->IsInside(x, y))
			{
				m_FoldButton->Touched();
				return m_FoldButton->GetEvent();
				break;
			}

			if (m_CallButton->IsInside(x, y))
			{
				m_CallButton->Touched();
				return m_CallButton->GetEvent();
				break;
			}

			if (m_RaiseButton->IsInside(x, y))
			{
				m_RaiseButton->Touched();
				return m_RaiseButton->GetEvent();
				break;
			}
			break;

		default:
			m_FoldButton->Normally();
			m_CallButton->Normally();
			m_RaiseButton->Normally();
		}
	}

	return ButtonEvent::ButtonEvent_Empty;
}