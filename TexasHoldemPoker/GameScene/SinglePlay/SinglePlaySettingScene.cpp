#include "SinglePlaySettingScene.h"
#include "../SceneManager.h"

SinglePlaySettingScene::SinglePlaySettingScene()
{

}

SinglePlaySettingScene::SinglePlaySettingScene(const SinglePlaySettingScene& other)
{

}

SinglePlaySettingScene::~SinglePlaySettingScene()
{

}

bool SinglePlaySettingScene::Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption)
{
	GameScene::Initialize(d2dEngine, audioEngine, gameOption);

	m_BackButton = new MainMenuButton;
	if (m_BackButton != NULL)
	{
		m_BackButton->InitializeEx(extEngine, 10,
			10,
			ScalingUI_Y(70, gameOption->GetHeight()),
			ScalingUI_Y(70, gameOption->GetHeight()),
			const_cast<WCHAR*>(L"¢¸"));

		m_BackButton->SetEvent(ButtonEvent::ButtonEvent_SinglePlay_Back);
	}
	else
		return false;

	m_StartButton = new MainMenuButton;
	if (m_StartButton != NULL)
	{
		m_StartButton->InitializeEx(extEngine, (extGameOption->GetWidth() / 2) - ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(800, extGameOption->GetHeight()),
			ScalingUI_X(400, extGameOption->GetWidth()),
			ScalingUI_Y(70, extGameOption->GetHeight()),
			const_cast<WCHAR*>(L"Start"));

		m_StartButton->SetEvent(ButtonEvent::ButtonEvent_Confirm);
	}
	else
		return false;

	m_TitleField = new TextOutputField;
	if (m_TitleField != NULL)
	{
		m_TitleField->Initialize(extEngine, (extGameOption->GetWidth() / 2) - ScalingUI_X(300, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()),
			ScalingUI_X(600, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()));

		m_TitleField->GetText()->SetText(const_cast<WCHAR*>(L"Single Play"));
		m_TitleField->GetText()->SetFontSize(m_TitleField->GetText()->GetFontSize() * 2);
		m_TitleField->GetText()->SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_TitleField->GetText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	else
		return false;

	m_NameField = new TextOutputField;
	if (m_NameField != NULL)
	{
		m_NameField->Initialize(extEngine, (extGameOption->GetWidth() / 2) - ScalingUI_X(550, extGameOption->GetWidth()),
			ScalingUI_Y(300, extGameOption->GetHeight()),
			ScalingUI_X(550, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()));

		m_NameField->CreateRectangle();
		m_NameField->GetText()->SetText(const_cast<WCHAR*>(L"Player Name : "));
		m_NameField->GetText()->SetFontSize(m_NameField->GetText()->GetFontSize() * 1.5);
		m_NameField->GetText()->SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT_TRAILING);
		m_NameField->GetText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	else
		return false;

	m_NumberField = new TextOutputField;
	if (m_NumberField != NULL)
	{
		m_NumberField->Initialize(extEngine, (extGameOption->GetWidth() / 2) - ScalingUI_X(550, extGameOption->GetWidth()),
			ScalingUI_Y(500, extGameOption->GetHeight()),
			ScalingUI_X(550, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()));

		m_NumberField->CreateRectangle();
		m_NumberField->GetText()->SetText(const_cast<WCHAR*>(L"Player Count(2 ~ 5) : "));
		m_NumberField->GetText()->SetFontSize(m_NumberField->GetText()->GetFontSize() * 1.5);
		m_NumberField->GetText()->SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT_TRAILING);
		m_NumberField->GetText()->SetTextHeightAlign(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	else
		return false;

	m_NameInputField = new CustomTextInputField;
	if (m_NameInputField != NULL)
	{
		m_NameInputField->Initialize(extEngine, (extGameOption->GetWidth() / 2) + ScalingUI_X(50, extGameOption->GetWidth()),
			ScalingUI_Y(300, extGameOption->GetHeight()),
			ScalingUI_X(550, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()));

	}

	m_NumberInputField = new NumberInputField;
	if (m_NumberInputField != NULL)
	{
		m_NumberInputField->Initialize(extEngine, (extGameOption->GetWidth() / 2) + ScalingUI_X(50, extGameOption->GetWidth()),
			ScalingUI_Y(500, extGameOption->GetHeight()),
			ScalingUI_X(550, extGameOption->GetWidth()),
			ScalingUI_Y(100, extGameOption->GetHeight()));

		m_NumberInputField->SetMaxDigit(1);
	}

	return true;
}

bool SinglePlaySettingScene::Render()
{
	m_BackButton->Render();
	m_StartButton->Render();
	m_TitleField->Render();
	m_NameField->Render();
	m_NumberField->Render();

	m_NameInputField->Render();
	m_NumberInputField->Render();
	return true;
}

bool SinglePlaySettingScene::Update()
{
	return true;
}

bool SinglePlaySettingScene::Release()
{
	SAFE_RELEASE_AND_DELETE(m_NumberInputField);
	SAFE_RELEASE_AND_DELETE(m_NameInputField);

	SAFE_RELEASE_AND_DELETE(m_NumberField);
	SAFE_RELEASE_AND_DELETE(m_NameField);
	SAFE_RELEASE_AND_DELETE(m_TitleField);

	SAFE_RELEASE_AND_DELETE(m_StartButton);
	SAFE_RELEASE_AND_DELETE(m_BackButton);
	return true;
}

void SinglePlaySettingScene::SummitData(int& playersNumber, std::wstring& playerName)
{
	if (m_PlayersNumber > 5)
		playersNumber = 5;
	else if (m_PlayersNumber < 2)
		playersNumber = 2;
	else
		playersNumber = m_PlayersNumber;

	if (m_PlayerName.size() <= 0 || m_PlayerName.size() > 16)
		playerName = L"Player";
	else
		playerName = m_PlayerName;
}

LRESULT SinglePlaySettingScene::SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);

	switch (message)
	{
	case WM_MOUSEMOVE:
		if (m_BackButton->IsInside(pt.x, pt.y))
		{
			m_BackButton->Touched();
			break;
		}
		else
			m_BackButton->Normally();

		if (m_StartButton->IsInside(pt.x, pt.y))
		{
			m_StartButton->Touched();
			break;
		}
		else
			m_StartButton->Normally();

		break;

	case WM_LBUTTONDOWN:
		if (m_BackButton->IsInside(pt.x, pt.y))
		{
			m_BackButton->Pressed();
			break;
		}

		if (m_StartButton->IsInside(pt.x, pt.y))
		{
			m_StartButton->Pressed();
			break;
		}

		break;

	case WM_LBUTTONUP:
		if (m_BackButton->IsInside(pt.x, pt.y))
		{
			m_BackButton->Touched();
			SceneManager::instance().EventListen(m_BackButton->GetEvent());
			break;
		}

		if (m_StartButton->IsInside(pt.x, pt.y))
		{
			m_StartButton->Touched();
			return true;
		}

		if (m_NameInputField->IsInside(pt.x, pt.y))
		{
			m_NameInputField->Selected();
		}
		else
			m_NameInputField->Normally();

		if (m_NumberInputField->IsInside(pt.x, pt.y))
		{
			m_NumberInputField->Selected();
		}
		else
			m_NumberInputField->Normally();
		break;

	case WM_CHAR:
		m_NameInputField->TextInputFieldFunc(hWnd, message, wParam, lParam);
		m_NumberInputField->TextInputFieldFunc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}