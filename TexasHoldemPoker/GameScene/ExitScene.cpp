#include "ExitScene.h"

ExitScene::ExitScene()
{
	m_BackButton = NULL;
	m_NoButton = NULL;
	m_YesButton = NULL;
	m_FadeOutRect = NULL;
	m_ExitGuideText = NULL;
}

ExitScene::ExitScene(const ExitScene& other)
{

}

ExitScene::~ExitScene()
{

}

bool ExitScene::Initialize(Direct2DEngine* d2dEngine, AudioEngine* audioEngine, GameOption* gameOption)
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

		m_BackButton->SetEvent(ButtonEvent::ButtonEvent_Exit_Back);
	}
	else
		return false;

	m_YesButton = new MainMenuButton;
	if (m_YesButton != NULL)
	{
		m_YesButton->InitializeEx(extEngine,
			extGameOption->GetWidth() / 2 - ScalingUI_X(600, extGameOption->GetWidth()),
			ScalingUI_Y(700, extGameOption->GetHeight()),
			ScalingUI_X(400, extGameOption->GetWidth()),
			ScalingUI_Y(70, extGameOption->GetHeight()),
			const_cast<WCHAR*>(L"Yes"));

		m_YesButton->SetEvent(ButtonEvent::ButtonEvent_Exit_Yes);
	}
	else
		return false;

	m_NoButton = new MainMenuButton;
	if (m_NoButton != NULL)
	{
		m_NoButton->InitializeEx(extEngine,
			extGameOption->GetWidth() / 2 + ScalingUI_X(200, extGameOption->GetWidth()),
			ScalingUI_Y(700, extGameOption->GetHeight()),
			ScalingUI_X(400, extGameOption->GetWidth()),
			ScalingUI_Y(70, extGameOption->GetHeight()),
			const_cast<WCHAR*>(L"No"));

		m_NoButton->SetEvent(ButtonEvent::ButtonEvent_Exit_No);
	}
	else
		return false;

	m_ExitGuideText = new CustomTextOutputField;
	if (m_ExitGuideText != NULL)
	{
		m_ExitGuideText->Initialize(extEngine,
			extGameOption->GetWidth() / 2 - ScalingUI_X(400, extGameOption->GetWidth()),
			ScalingUI_Y(450, extGameOption->GetHeight()),
			ScalingUI_X(800, extGameOption->GetWidth()),
			ScalingUI_Y(200, extGameOption->GetHeight()));

		m_ExitGuideText->SetTextContent(const_cast<WCHAR*>(L"Do you want to quit the game?"));
		m_ExitGuideText->GetText()->SetFontSize(m_ExitGuideText->GetText()->GetFontSize() * 1.5);
		m_ExitGuideText->GetText()->SetTextWidthAlign(DWRITE_TEXT_ALIGNMENT_CENTER);
	}
	else
		return false;

	m_FadeOutRect = new CRectangle;
	if (m_FadeOutRect != NULL)
	{
		m_FadeOutRect->Initialize(extEngine, 0, 0, extGameOption->GetWidth(), extGameOption->GetHeight());
		m_FadeOutRect->SetFill(true);
		m_FadeOutRect->SetColor(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.5f));
		m_FadeOutRect->SetFillColor(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.5f));
	}
	else
		return false;

	return true;
}

bool ExitScene::Render()
{
	m_FadeOutRect->Draw();
	m_BackButton->Render();
	m_YesButton->Render();
	m_NoButton->Render();
	m_ExitGuideText->Render();
	return true;
}

bool ExitScene::Update()
{
	return true;
}

bool ExitScene::Release()
{
	SAFE_RELEASE_AND_DELETE(m_FadeOutRect);
	SAFE_RELEASE_AND_DELETE(m_ExitGuideText);
	SAFE_RELEASE_AND_DELETE(m_NoButton);
	SAFE_RELEASE_AND_DELETE(m_YesButton);
	SAFE_RELEASE_AND_DELETE(m_BackButton);

	return true;
}

LRESULT ExitScene::SceneProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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

		if (m_YesButton->IsInside(pt.x, pt.y))
		{
			m_YesButton->Touched();
			break;
		}
		else
			m_YesButton->Normally();

		if (m_NoButton->IsInside(pt.x, pt.y))
		{
			m_NoButton->Touched();
			break;
		}
		else
			m_NoButton->Normally();
		break;

	case WM_LBUTTONDOWN:
		if (m_BackButton->IsInside(pt.x, pt.y))
		{
			m_BackButton->Pressed();
			break;
		}

		if (m_YesButton->IsInside(pt.x, pt.y))
		{
			m_YesButton->Pressed();
			break;
		}

		if (m_NoButton->IsInside(pt.x, pt.y))
		{
			m_NoButton->Pressed();
			break;
		}

		break;

	case WM_LBUTTONUP:
		if (m_BackButton->IsInside(pt.x, pt.y))
		{
			SceneManager::instance().EventListen(m_BackButton->GetEvent());
			break;
		}

		if (m_YesButton->IsInside(pt.x, pt.y))
		{
			SceneManager::instance().EventListen(m_YesButton->GetEvent());
			break;
		}

		if (m_NoButton->IsInside(pt.x, pt.y))
		{
			SceneManager::instance().EventListen(m_NoButton->GetEvent());
			break;
		}
		break;
	}
	return 0;
}